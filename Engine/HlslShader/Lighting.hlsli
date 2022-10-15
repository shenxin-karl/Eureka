#ifndef _LIGHTING_HLSLI_
#define _LIGHTING_HLSLI_

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
	float3 direction;
	float  spotAngle;
	float4 viewSpacePosition;
};

struct SpotLight {
	float3 color;
	float  intensity;
	float3 position;
	float  range;
};

#define MAX_TILE_POINT_LIGHT_NUM 80
#define MAX_TILE_SPOT_LIGHT_NUM 80

struct LightList {
	uint numPointLights;
	uint pointLightIndices[MAX_TILE_POINT_LIGHT_NUM];
	uint numSpotLights;
	uint spotLightIndices[MAX_TILE_POINT_LIGHT_NUM];
};

#endif
