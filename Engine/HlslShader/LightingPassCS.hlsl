#include "Common.hlsli"

cbuffer CbLighting : register(b0) {
	float4   gLightDirection;
    float4   gLightRadiance;
    float4x4 gProj;
    float3   gCameraPosition;
    float    gWidth;
    float3   gViewLeftTop;
    float    gHeight;
    float3   gViewDownDir;
    float    gNear;
    float3   gViewRightDir;
    float    gFar; 
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
	return (cin.DispatchThreadID.xy) / (float2(gWidth, gHeight) - 1.0);
}

float NdcDepthToViewDepth(float zNdc) {
	float magic = (gFar - gNear) / gNear;
    return 1.0 / (magic * zNdc + 1.0);
}

float4 CalcWorldPosition(float2 uv)
{
	float zNdc = gDepthMap.SampleLevel(gSamLinearClamp, uv, 0).x;
    float4 pos = float4(uv.x * 2.0 - 1.0, uv.y * 2.0 - 1.0, zNdc * 2.0 - 1.0, 1.0);
    //float4 pos = float4(uv.x * 2.0 - 1.0, uv.y * 2.0 - 1.0, zNdc, 1.0);
 
    float4 WorldPos = mul(gMatInvViewProj, pos);
    WorldPos.xyz /= WorldPos.w;
    return (WorldPos);

#if 0
    float3 direction = normalize(gViewLeftTop.xyz + uv.x * gViewRightDir.xyz + uv.y * gViewDownDir.xyz); 
    float3 worldPosition = gCameraPosition.xyz + zView * direction;
    return worldPosition;
#endif
}

[numthreads(16, 16, 1)]
void CS(ComputeIn cin) {
    float2 uv = CalcTexcoord(cin);
    gLightingBuffer[cin.DispatchThreadID.xy] = float4(CalcWorldPosition(uv));

    float3 Color = gBuffer0.SampleLevel(gSamPointClamp, uv, 0);
    gLightingBuffer[cin.DispatchThreadID.xy] = float4(Color, 1.0);

}