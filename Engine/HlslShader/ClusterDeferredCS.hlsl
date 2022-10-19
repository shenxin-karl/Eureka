#include "Lighting.hlsli"

cbuffer CbCluster : register(b0) {
    uint gNumCluster;
    uint gWidth;
};

RWStructuredBuffer<LightList>		gLightList			 : register(u0);
StructuredBuffer<PointLight>		gPointList			 : register(t0);
StructuredBuffer<SpotLight>			gSpotLight			 : register(t1);
StructuredBuffer<float4>			gPointBoundingSphere : register(t2);
StructuredBuffer<float4>			gSpotBoundingSphere  : register(t3);
StructuredBuffer<ClusterFrustum>	gClusterFrustums	 : register(t4);	

struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           
    uint3 GroupThreadID     : SV_GroupThreadID;     
    uint3 DispatchThreadID  : SV_DispatchThreadID;  
    uint  GroupIndex        : SV_GroupIndex;        
};

groupshared ClusterFrustum clusterFrustum[CBDR_MAX_CLUSTER_DIMENSION];

[numthreads(8, 8, 1)]
void CS(ComputeIn cin) {
	uint tileIdx = CalcClusterIndex(gWidth, cin.DispatchThreadID.xy, gNumCluster);

    // ��� Tile ��ǰ gNumCluster ���߳�, ��ʼ���� tile �� ��׶�建��
    uint threadClusterId = cin.DispatchThreadID.x % CBDR_TILE_DIMENSION;
    if (threadClusterId < gNumCluster) {
	    gLightList[tileIdx + threadClusterId].numPointLights = 0;
        gLightList[tileIdx + threadClusterId].numSpotLights = 0;
        clusterFrustum[threadClusterId] = gClusterFrustums[tileIdx + threadClusterId];
    }
    GroupMemoryBarrierWithGroupSync();

    // �޳����Դ����
    uint numPointLight, trash;
    gPointList.GetDimensions(numPointLight, trash);
    for (uint lightIndex = 0; lightIndex < numPointLight; lightIndex += CBDR_TILE_SIZE) {
        bool isFrustum = true;
	    float4 boundingSphere = gPointBoundingSphere[lightIndex];

        // �������� cluster �� 0 ����׶��, ���� xy ���ж�
        [unrool] for (uint i = 0; i < 4; ++i) {
	        float d = dot(clusterFrustum[0].frustumPlanes[i], float4(boundingSphere.xyz, 1.0));
            isFrustum = isFrustum && (d >= -boundingSphere.w);
        }
        if (isFrustum) {
            // ����ÿһ�� cluster, �õ���׶��, �ж��Ƿ�͵��Դ��
	        for (uint clusterIndex = 0; clusterIndex < gNumCluster; ++clusterIndex) {
		        isFrustum = true;
                [unroll] for (uint i = 4; i < 6; ++i) {     // ����ֻ��Ҫ�ж� near �� far
	                float d = dot(clusterFrustum[clusterIndex].frustumPlanes[i], float4(boundingSphere.xyz, 1.0));
                    isFrustum = isFrustum && (d >= -boundingSphere.w);
                }
				[branch] if (isFrustum) {
					uint listIndex = 0;
				    InterlockedAdd(gLightList[tileIdx + clusterIndex].numPointLights, 1, listIndex);
		            if (lightIndex < MAX_TILE_POINT_LIGHT_NUM)
						gLightList[tileIdx + clusterIndex].numPointLights = listIndex;
	            }
	        }
        }
    }
}