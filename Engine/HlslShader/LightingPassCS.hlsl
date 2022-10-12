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
    float    padding0;
    float3   gViewRightDir;
    float    padding1; 
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
	return (cin.DispatchThreadID.xy + 0.5) / float2(gWidth, gHeight);
}

float NdcDepthToViewDepth(float zNdc) {
    // 龙书上是, gProj[3][2] / (zNdc - gProj[2][2]), 因为我们传过来的矩阵没有转置, 所以 32 变成 23
	float viewZ = gProj[2][3] / (zNdc - gProj[2][2]);
    return viewZ;
}

float3 CalcWorldPosition(float2 uv) {
	float zNdc = gDepthMap.SampleLevel(gSamLinearClamp, uv, 0).x;
    float zView = NdcDepthToViewDepth(zNdc);
    return zView / 1000.f;

#if 0
    float3 direction = normalize(gViewLeftTop.xyz + uv.x * gViewRightDir.xyz + uv.y * gViewDownDir.xyz); 
    float3 worldPosition = gCameraPosition.xyz + zView * direction;
    return worldPosition;
#endif
}

[numthreads(16, 16, 1)]
void CS(ComputeIn cin) {
    float2 uv = CalcTexcoord(cin);
    // float3 worldPosition = normalize(CalcWorldPosition(uv));
    // gLightingBuffer[cin.DispatchThreadID.xy] = float4(worldPosition * 0.5 + 0.5, 1.0);
    gLightingBuffer[cin.DispatchThreadID.xy] = float4(CalcWorldPosition(uv), 1.0);
}