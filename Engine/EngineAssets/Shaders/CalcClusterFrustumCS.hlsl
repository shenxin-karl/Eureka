#include "Lighting.hlsli"

struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           
    uint3 GroupThreadID     : SV_GroupThreadID;     
    uint3 DispatchThreadID  : SV_DispatchThreadID;  
    uint  GroupIndex        : SV_GroupIndex;        
};

cbuffer CbParam : register(b0) {
	float4x4 gProj;
    uint2    gRenderTargetSize;
    uint     gNumCluster;
    float    padding0;
};

RWStructuredBuffer<ClusterFrustum> gOutputClusterFrustum : register(u0);

#define NUM_THREAD 256

[numthreads(NUM_THREAD, 1, 1)]
void CS(ComputeIn cin) {
    // 每个线程负责一个 Tile 的所有 Cluster 的视锥体计算
	uint index = cin.GroupID.x * NUM_THREAD + cin.GroupIndex;
    uint rowTileSize = DivideByMultiple(gRenderTargetSize.x, CBDR_TILE_DIMENSION);
    uint2 tileGroupID = uint2(index % rowTileSize, index / rowTileSize);

    float2 tileScale = float2(gRenderTargetSize.xy) * rcp(float(2.0 * CBDR_TILE_DIMENSION));
    float2 tileBias = tileScale - float2(tileGroupID.xy);

    float4 c1 = float4(gProj._11 * tileScale.x, 0.0f, tileBias.x, 0.0f);
    float4 c2 = float4(0.0f, -gProj._22 * tileScale.y, tileBias.y, 0.0f);
    float4 c4 = float4(0.0f, 0.0f, 1.0f, 0.0f);

    ClusterFrustum frustum;
    // Sides
    frustum.frustumPlanes[0] = c4 - c1;
    frustum.frustumPlanes[1] = c4 + c1;
    frustum.frustumPlanes[2] = c4 - c2;
    frustum.frustumPlanes[3] = c4 + c2;

    // Normalize frustum planes (near/far already normalized)
    [unroll] for (uint i = 0; i < 4; ++i) 
        frustum.frustumPlanes[i] *= rcp(length(frustum.frustumPlanes[i].xyz));

    uint tileStartIndex = index * gNumCluster;
    for (uint clusterIndex = 0; clusterIndex < gNumCluster; ++clusterIndex) {
        frustum.frustumPlanes[4] = float4(0.0, 0.0, +1.0, -kDepthSlicing16[clusterIndex]);
        frustum.frustumPlanes[5] = float4(0.0, 0.0, -1.0,  kDepthSlicing16[clusterIndex+1]);
	    gOutputClusterFrustum[tileStartIndex + clusterIndex] = frustum;
    }
}