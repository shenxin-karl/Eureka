#include "Common.hlsli"
#include "CookTorrance.hlsli"
#include "Lighting.hlsli"

cbuffer CbLighting : register(b0) {
	DirectionalLight gDirectionalLight;
    float4x4         gInvViewProj;
    float3           gCameraPosition;
    float            gClosedIntervalOfHeight;       // height - 1
    float            gClosedIntervalOfWidth;        // width - 1
};

Texture2D<float3> gBuffer0  : register(t0);
Texture2D<float3> gBuffer1  : register(t1);
Texture2D<float3> gBuffer2  : register(t2);
Texture2D<float>  gDepthMap : register(t3);

StructuredBuffer<PointLight> gPointLights     : register(t4);      
StructuredBuffer<LightList>  gTileLightLists  : register(t6);       

RWTexture2D<float4> gLightingBuffer : register(u0);

struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           // 3D index of the thread group in the dispatch.
    uint3 GroupThreadID     : SV_GroupThreadID;     // 3D index of local thread ID in a thread group.
    uint3 DispatchThreadID  : SV_DispatchThreadID;  // 3D index of global thread ID in the dispatch.
    uint  GroupIndex        : SV_GroupIndex;        // Flattened local index of the thread within a thread group.
};

float2 CalcTexcoord(ComputeIn cin) {
	return (cin.DispatchThreadID.xy) / float2(gClosedIntervalOfWidth, gClosedIntervalOfHeight);
}

/*
	from: https://www.gamedev.net/forums/topic/703933-world-position-from-depth/5413262/
	float3 get_world_position_from_depth( float2 uv, float depth ) {
		float4 ndc = float4( uv * 2.0f - 1.0f, depth, 1.0f );
		ndc.y *= -1.0f;
		float4 wp = mul( ndc, PM_INVERSE_VIEW_PROJECTION );
		return ( wp / wp.w ).xyz;
	}
 */
float4 CalcWorldPosition(float2 uv)
{
	float zNdc = gDepthMap.SampleLevel(gSamLinearClamp, uv, 0).x;
    float4 pos = float4(uv * 2.0 - 1.0, zNdc, 1.0);
    pos.y *= -1.0;
    float4 worldPos = mul(gInvViewProj, pos);
    worldPos.xyz /= worldPos.w;
    return worldPos;
}

void SampleAoRoughnessMetallic(float2 uv, inout float ao, inout float roughness, inout float metallic) {
	float3 sampleColor = gBuffer2.SampleLevel(gSamPointClamp, uv, 0).rgb;
    ao = sampleColor.x;
    roughness = sampleColor.g;
    metallic = sampleColor.b;
}

[numthreads(TBDR_TILE_DIMENSION, TBDR_TILE_DIMENSION, 1)]
void CS(ComputeIn cin) {
    float2 uv = CalcTexcoord(cin);
    float3 worldPosition = CalcWorldPosition(uv);

    float4 diffuseAlbedo = float4(gBuffer0.SampleLevel(gSamPointClamp, uv, 0), 1.0);

    float3 N = gBuffer1.SampleLevel(gSamPointClamp, uv, 0) * 2.0 - 1.0;
    float3 V = normalize(gCameraPosition - worldPosition);

    float ao = 1.0, roughness = 1.0, metallic = 1.0;
    SampleAoRoughnessMetallic(uv, ao, roughness, metallic);

    MaterialData materialData = calcMaterialData(diffuseAlbedo, roughness, metallic);

    // directional light 
	float3 radiance = ComputeDirectionLight(gDirectionalLight, materialData, N, V);

    // ambient light
	radiance += ComputeAmbientLight(gDirectionalLight, materialData, ao);

    // point light
	uint2 texDim;
	gDepthMap.GetDimensions(texDim.x, texDim.y);
	uint tileIndex = CalcTileIndex(texDim.x, cin.GroupID.xy);
    uint numPointLights = min(gTileLightLists[tileIndex].numPointLights, MAX_TILE_POINT_LIGHT_NUM);
    for (uint i = 0; i < numPointLights; ++i) {
	    uint lightIndex = gTileLightLists[tileIndex].pointLightIndices[i];
        PointLight pointLight = gPointLights[lightIndex];
		radiance += ComputePointLight(pointLight, materialData, N, V, worldPosition);
    }

    gLightingBuffer[cin.DispatchThreadID.xy] = float4(radiance, 1.0);


}