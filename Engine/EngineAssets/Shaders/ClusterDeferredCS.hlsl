#include "Lighting.hlsli"

cbuffer CbCluster : register(b0) {
    uint gNumCluster;
    uint gWidth;
};

RWStructuredBuffer<LightList>		gLightList			 : register(u0);
StructuredBuffer<ClusterFrustum>	gClusterFrustums	 : register(t0);	
StructuredBuffer<PointLight>		gPointList			 : register(t1);
StructuredBuffer<float4>			gPointBoundingSphere : register(t2);

#if 0

StructuredBuffer<SpotLight>			gSpotLight			 : register(t3);
StructuredBuffer<float4>			gSpotBoundingSphere  : register(t4);

#endif

struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           
    uint3 GroupThreadID     : SV_GroupThreadID;     
    uint3 DispatchThreadID  : SV_DispatchThreadID;  
    uint  GroupIndex        : SV_GroupIndex;        
};

[numthreads(CBDR_THREAD_X, CBDR_THREAD_Y, 1)]
void CS(ComputeIn cin) {
	uint2 tileParam = CalcClusterTileParam(
	    gWidth, 
	    cin.DispatchThreadID.xy, 
	    gNumCluster
    );

    uint tileStartIndex = tileParam.x;
    uint tileGroupIndex = tileParam.y;
    if (tileGroupIndex < gNumCluster) {
	    gLightList[tileStartIndex + tileGroupIndex].numPointLights = 0;
	    gLightList[tileStartIndex + tileGroupIndex].numSpotLights = 0;
    }
    GroupMemoryBarrierWithGroupSync();

    // 剔除点光源数据
    uint numPointLight, trash;
    gPointList.GetDimensions(numPointLight, trash);
    uint pointLimit = numPointLight * gNumCluster;
    for (uint index = tileGroupIndex; index < pointLimit; index += CBDR_TILE_SIZE) {
		uint clusterIndex = index / numPointLight;
        uint tileClusterIndex = tileStartIndex + clusterIndex;
        uint pointIndex = index % numPointLight;

        bool isFrustum = true;
	    float4 boundingSphere = gPointBoundingSphere[pointIndex];
        float4 boundingCenter = float4(boundingSphere.xyz, 1.0);
        ClusterFrustum frustum = gClusterFrustums[tileClusterIndex];
        float negativeW = -boundingSphere.w;

        [unroll] for (uint i = 0; i < 6; ++i) {
	        float d = dot(frustum.frustumPlanes[i], boundingCenter);
            isFrustum = isFrustum && (d >= negativeW);
        }

        [branch] if (isFrustum) {
			uint listIndex = 0;
		    InterlockedAdd(gLightList[tileClusterIndex].numPointLights, 1, listIndex);
            if (listIndex < MAX_TILE_POINT_LIGHT_NUM)
				gLightList[tileClusterIndex].pointLightIndices[listIndex] = pointIndex;
        }
    }

#if 0
    // 剔除聚光灯数据
    uint numSpotLight;
    gSpotLight.GetDimensions(numSpotLight, trash);
    for (uint spotIndex = tileGroupIndex; spotIndex < numSpotLight; spotIndex += CBDR_THREAD_GROUP_SIZE) {
        bool isFrustum = true;
	    float4 boundingSphere = gSpotBoundingSphere[spotIndex];

        // 这里先拿 cluster 的 0 号视锥体, 做好 xy 的判断
        [unroll(4)] for (uint i = 0; i < 4; ++i) {
	        float d = dot(clusterFrustum[0].frustumPlanes[i], float4(boundingSphere.xyz, 1.0));
            isFrustum = isFrustum && (d >= -boundingSphere.w);
        }
        [branch] if (isFrustum) {
            // 遍历每一个 cluster, 拿到视锥体, 判断是否和点光源求交
	        for (uint clusterIndex = 0; clusterIndex < gNumCluster; ++clusterIndex) {
		        isFrustum = true;
                [unroll] for (uint i = 4; i < 6; ++i) {     // 这里只需要判断 near 和 far
	                float d = dot(clusterFrustum[clusterIndex].frustumPlanes[i], float4(boundingSphere.xyz, 1.0));
                    isFrustum = isFrustum && (d >= -boundingSphere.w);
                }
				[branch] if (isFrustum) {
					uint listIndex = 0;
				    InterlockedAdd(gLightList[tileIdx + clusterIndex].numSpotLights, 1, listIndex);
		            if (spotIndex < MAX_TILE_SPOT_LIGHT_NUM)
						gLightList[tileIdx + clusterIndex].numSpotLights = listIndex;
	            }
	        }
        }
    }
#endif
}