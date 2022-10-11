#include "Common.hlsli"

cbuffer CbLighting : register(b0) {
	float4   gLightDirection;
    float4   gLightRadiance;
    float4x4 gProj;
    float4   gCameraPosition;
    float4   gViewLeftTop;
    float4   gViewDownDir;
    float4   gViewRightDir;
};

Texture2D<float3> gBuffer0  : register(t0);
Texture2D<float3> gBuffer1  : register(t1);
Texture2D<float3> gBuffer2  : register(t2);
Texture2D<float>  gDepthMap : register(t3);

RWTexture2D<float4> gLightingBuffer : register(u0);

struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           // 3D index of the thread group in the dispatch.
    uint3 GroupThreadID     : SV_GroupThreadID;     // 3D index of local thread ID in a thread group.
    uint3 DispatchThreadID  : SV_DispatchThreadID;  // 3D index of global thread ID in the dispatch.
    uint  GroupIndex        : SV_GroupIndex;        // Flattened local index of the thread within a thread group.
};

float2 CalcTexcoord(ComputeIn cin) {
	float2 bufferDimes;
    gDepthMap.GetDimensions(bufferDimes.x, bufferDimes.y);
	return cin.DispatchThreadID.xy + 0.5 / bufferDimes;
}

float NdcDepthToViewDepth(float zNdc) {
    // 龙书上是, gProj[3][2] / (zNdc - gProj[2][2]), 因为我们传过来的矩阵没有转置, 所以 32 变成 23
	float viewZ = gProj[2][3] / (zNdc - gProj[2][2]);
    return viewZ;
}

float3 CalcWorldPosition(float2 uv) {
	float zNdc = gDepthMap.SampleLevel(gSamLinearClamp, uv, 0).x;
    float zView = NdcDepthToViewDepth(zNdc);
    float3 direction = normalize(gViewLeftTop.xyz + uv.x * gViewRightDir.xyz + uv.y * gViewDownDir.xyz); 
    float3 worldPosition = gCameraPosition.xyz + zView * direction;
    return worldPosition;
}

[numthreads(16, 16, 1)]
void CS(ComputeIn cin) {
    float2 uv = CalcTexcoord(cin);
    float3 worldPosition = CalcWorldPosition(uv);
    gLightingBuffer[cin.DispatchThreadID.xy] = float4(worldPosition, 1.0);
}