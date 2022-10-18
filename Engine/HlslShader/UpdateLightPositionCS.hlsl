#include "Lighting.hlsli"

cbuffer CbView : register(b0) {
	float4x4 gView;
};

#if defined(UPDATE_POINT_LIGHT)
	RWStructuredBuffer<PointLight> gPointList : register(u0);
#else
	RWStructuredBuffer<SpotLight>  gSpotList : register(u0);
#endif

struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           // 3D index of the thread group in the dispatch.
    uint3 GroupThreadID     : SV_GroupThreadID;     // 3D index of local thread ID in a thread group.
    uint3 DispatchThreadID  : SV_DispatchThreadID;  // 3D index of global thread ID in the dispatch.
    uint  GroupIndex        : SV_GroupIndex;        // Flattened local index of the thread within a thread group.
};

#define NUM_THREAD 32

[numthreads(NUM_THREAD, 1, 1)]
void CS(ComputeIn cin) {
	uint index = cin.DispatchThreadID.y * NUM_THREAD + cin.DispatchThreadID.x;

#if defined(UPDATE_POINT_LIGHT)
    float3 position = gPointList[index].position;
    gPointList[index].viewSpacePosition = mul(gView, float4(position, 1.0));
#else
	float3 position = gSpotList[index].position;
    gSpotList[index].viewSpaceBoundingSphereCenter = mul(gView, float4(position, 1.0)).xyz;
#endif
}