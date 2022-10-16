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
	float3 color;
	float  intensity;
	float3 position;
	float  range;
};

#define MAX_TILE_POINT_LIGHT_NUM	80
#define MAX_TILE_SPOT_LIGHT_NUM		80
#define TBDR_TILE_DIMENSION			16
#define TBDR_TILE_SIZE				(TBDR_TILE_DIMENSION * TBDR_TILE_DIMENSION)

struct LightList {
	uint numPointLights;
	uint pointLightIndices[MAX_TILE_POINT_LIGHT_NUM];
	uint numSpotLights;
	uint spotLightIndices[MAX_TILE_POINT_LIGHT_NUM];
};

uint CalcTileIndex(uint renderTargetWidth, uint2 groupId) {
	uint numWidthTile = (renderTargetWidth.x + TBDR_TILE_DIMENSION-1) / TBDR_TILE_DIMENSION;
	uint tileIndex = groupId.y * numWidthTile + groupId.x;
	return tileIndex;
}

#endif
