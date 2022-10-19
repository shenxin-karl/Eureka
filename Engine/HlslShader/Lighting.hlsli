#ifndef _LIGHTING_HLSLI_
#define _LIGHTING_HLSLI_

#ifndef SHARED_STRUCT
	#define SHARED_STRUCT 
#endif

struct DirectionalLight {
	float3 ambientColor;
	float  ambientIntensity;
	float3 directionalColor;
	float  directionalIntensity;
	float3 direction;
	float  padding0;
};

struct PointLight {
	float3 color;
	float  intensity;
	float3 position;
	float  range;
	float4 viewSpacePosition;
};

struct SpotLight {
	float3	color;
	float	intensity;
	float3	position;
	float	range;
	float3  direction;
	float	boundingSphereRadius;
	float3  viewSpaceBoundingSphereCenter;
	float	innerConeCosTheta;
	float	outerConeCosTheta;
};

#define MAX_TILE_POINT_LIGHT_NUM	160
#define MAX_TILE_SPOT_LIGHT_NUM		160
#define TBDR_TILE_DIMENSION			16
#define TBDR_TILE_SIZE				(TBDR_TILE_DIMENSION * TBDR_TILE_DIMENSION)
#define CBDR_TILE_DIMENSION			64
#define CBDR_CLUSTER_DIMENSION		16
#define CBDR_TILE_SIZE				(CBDR_TILE_DIMENSION * CBDR_TILE_DIMENSION)

struct LightList {
	uint numPointLights;
	uint pointLightIndices[MAX_TILE_POINT_LIGHT_NUM];
	uint numSpotLights;
	uint spotLightIndices[MAX_TILE_POINT_LIGHT_NUM];
};

struct ClusterFrustum {
	float4 frustumPlanes[6];
};

uint DivideByMultiple(uint value, uint alignment) {
	return (value + alignment - 1) / alignment;
}

uint CalcTileIndex(uint renderTargetWidth, uint2 groupId) {
	uint numWidthTile = DivideByMultiple(renderTargetWidth, TBDR_TILE_DIMENSION);
	uint tileIndex = groupId.y * numWidthTile + groupId.x;
	return tileIndex;
}

uint CalcClusterIndex(uint renderTargetWidth, uint2 dispatchID, uint zClusterSize) {
	uint xTileSize = DivideByMultiple(renderTargetWidth, CBDR_TILE_DIMENSION);
	uint yTileID = dispatchID.y / CBDR_TILE_DIMENSION;
	uint xTileID = dispatchID.x / CBDR_TILE_DIMENSION;
	uint startIndex = (yTileID * xTileSize + xTileID) * zClusterSize;
	return startIndex;
}

#endif
