#include "Lighting.hlsli"

Texture2D<float> gDepthMap : register(t0);
StructuredBuffer<PointLight> gPointLists : register(t1);
RWStructuredBuffer<LightList> gTileLightLists : register(u0);

groupshared uint sMinZ;
groupshared uint sMaxZ;

cbuffer gCbTiled {
	float4x4 gView;
	float4x4 gProj;
	float    gNear;
	float	 gFar;
	float    gFarMultiplyNear;		// far * near
	float	 gFarMinusNear;			// far - near
};

float ViewDepth(float depth) {
	return (gFarMultiplyNear) / (gFar - depth * (gFarMinusNear));
}

struct ComputeIn {
    uint3 GroupID           : SV_GroupID;           // 3D index of the thread group in the dispatch.
    uint3 GroupThreadID     : SV_GroupThreadID;     // 3D index of local thread ID in a thread group.
    uint3 DispatchThreadID  : SV_DispatchThreadID;  // 3D index of global thread ID in the dispatch.
    uint  GroupIndex        : SV_GroupIndex;        // Flattened local index of the thread within a thread group.
};

#define TILE_DIM 16
#define TILE_SIZE (TILE_DIM * TILE_DIM)

[numthreads(TILE_DIM, TILE_DIM, 1)]
void CS(ComputeIn cin) {
	// 每个 group 负责一块 tile 的计算
	// step 1 initialize tile
	uint tileIndex = cin.GroupID.y * TILE_DIM + cin.GroupID.y;
	if (cin.GroupIndex == 0) {
		gTileLightLists[tileIndex].numPointLights = 0;
		gTileLightLists[tileIndex].numSpotLights = 0;
		sMinZ = 0x7F7FFFFF;      // Max float
		sMaxZ = 0;
	}
	GroupMemoryBarrierWithGroupSync();

	// step 2 calc min max depth
	float depthBuffer = gDepthMap[cin.DispatchThreadID.xy].r;
	float depth = ViewDepth(depthBuffer);

	// Avoid shading skybox/background or otherwise invalid pixels
	if (depth >= gNear && depth < gFar) {
		InterlockedMin(sMinZ, asuint(depth));
		InterlockedMax(sMaxZ, asuint(depth));
	}
    GroupMemoryBarrierWithGroupSync();

	// step 3 Cull lights for this tile

	float minTileZ = asfloat(sMinZ);
    float maxTileZ = asfloat(sMaxZ);

	float2 texDimes;
	gDepthMap.GetDimensions(texDimes.x, texDimes.y);
	float2 tileScale = texDimes * rcp(float(2.0 * TILE_DIM));
    float2 tileBias = tileScale - float2(cin.GroupID.xy);

    float4 c1 = float4(gProj._11 * tileScale.x, 0.0f, tileBias.x, 0.0f);
	float4 c2 = float4(0.0f, -gProj._22 * tileScale.y, tileBias.y, 0.0f);
    float4 c4 = float4(0.0f, 0.0f, 1.0f, 0.0f);

	// Derive frustum planes
    float4 frustumPlanes[6];
    // Sides
    frustumPlanes[0] = c4 - c1;
    frustumPlanes[1] = c4 + c1;
    frustumPlanes[2] = c4 - c2;
    frustumPlanes[3] = c4 + c2;
    // Near/far
    frustumPlanes[4] = float4(0.0f, 0.0f,  1.0f, -minTileZ);
    frustumPlanes[5] = float4(0.0f, 0.0f, -1.0f,  maxTileZ);
    
    // Normalize frustum planes (near/far already normalized)
    [unroll]
	for (uint i = 0; i < 4; ++i) 
        frustumPlanes[i] *= rcp(length(frustumPlanes[i].xyz));

	uint pointSizes, dummy;
    gPointLists.GetDimensions(pointSizes, dummy);
	for (uint lightIndex = cin.GroupIndex; lightIndex < pointSizes; lightIndex += TILE_SIZE) {
        PointLight light = gPointLists[lightIndex];
		// Cull: point light sphere vs tile frustum
        bool inFrustum = true;
		[unroll] for (uint i = 0; i < 6; ++i) {
			float d = dot(frustumPlanes[i], light.viewSpacePosition);
            inFrustum = inFrustum && (d >= -light.range);
		}
		 [branch] if (inFrustum) {
            // Append light to list
            // Compaction might be better if we expect a lot of lights
            uint listIndex;
            InterlockedAdd(gTileLightLists[tileIndex].numPointLights, 1, listIndex);
			if (listIndex < MAX_TILE_POINT_LIGHT_NUM) 
				gTileLightLists[tileIndex].pointLightIndices[listIndex] = lightIndex;
		 }
	}
}