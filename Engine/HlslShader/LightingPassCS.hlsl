#include "Common.hlsli"
#include "CookTorrance.hlsli"

cbuffer CbLighting : register(b0) {
	float3   gLightDirection;
    float    gClosedIntervalOfWidth;        // width - 1
    float3   gLightRadiance;
    float    gClosedIntervalOfHeight;       // height - 1
    float4x4 gInvViewProj;
    float3   gCameraPosition;
    float    padding0;
};

Texture2D<float3> gBuffer0  : register(t0);
Texture2D<float3> gBuffer1  : register(t1);
Texture2D<float3> gBuffer2  : register(t2);
Texture2D         gDepthMap : register(t3);

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

float4 CalcWorldPosition(float2 uv)
{
	float zNdc = gDepthMap.SampleLevel(gSamLinearClamp, uv, 0).x;
    float4 pos = float4(uv.x * 2.0 - 1.0, uv.y * 2.0 - 1.0, zNdc * 2.0 - 1.0, 1.0);
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

[numthreads(16, 16, 1)]
void CS(ComputeIn cin) {
    float2 uv = CalcTexcoord(cin);
    float3 worldPosition = CalcWorldPosition(uv);
    float4 diffuseAlbedo = float4(gBuffer0.SampleLevel(gSamPointClamp, uv, 0), 1.0);

    float3 N = gBuffer1.SampleLevel(gSamPointClamp, uv, 0) * 2.0 - 1.0;
    float3 V = normalize(gCameraPosition - worldPosition);

    float ao = 1.0, roughness = 1.0, metallic = 1.0;
    SampleAoRoughnessMetallic(uv, ao, roughness, metallic);

    MaterialData materialData = calcMaterialData(diffuseAlbedo, roughness, metallic);

    LightData light = (LightData)0;
    light.strength = gLightRadiance;
    light.direction = gLightDirection;

    float3 ambient = 0.1 * diffuseAlbedo;
	float3 radiance = ComputeDirectionLight(light, materialData, N, V);
    //radiance += ambient;
    gLightingBuffer[cin.DispatchThreadID.xy] = float4(radiance, 1.0);
}