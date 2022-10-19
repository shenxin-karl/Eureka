#include "Lighting.hlsli"

cbuffer CbView : register(b0) {
	float4x4 gView;
};

#if defined(UPDATE_POINT_LIGHT)
	StructuredBuffer<PointLight> gPointList : register(t0);
#else
	StructuredBuffer<SpotLight>  gSpotList  : register(t0);
#endif

RWStructuredBuffer<float4> gOutputBoundingSphere : register(u0);

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
	float radius = gPointList[index].range;
    float3 boundingSphereCenter = mul(gView, float4(position, 1.0)).xyz;
	gOutputBoundingSphere[index] = float4(boundingSphereCenter, radius);
#else
	float3 position = gSpotList[index].position;
	float radius = gSpotList[index].boundingSphereRadius;
    float3 boundingSphereCenter = mul(gView, float4(position, 1.0)).xyz;
	gOutputBoundingSphere[index] = float4(boundingSphereCenter, radius);
#endif
}