#ifndef _LIGHTING_HLSLI_
#define _LIGHTING_HLSLI_

#if defined(__cplusplus)
	#include <cstdint>
	#include <Math/MathStd.hpp>
	#define SHARED_STRUCT using float2 = Math::float2;\
						  using float3 = Math::float3;\
						  using float4 = Math::float4;\
						  using float3x3 = Math::float3x3;\
						  using float4x4 = Math::float4x4;\
						  using uint = std::uint32_t;
#else
	#define SHARED_STRUCT 
#endif

struct DirectionalLight {
	SHARED_STRUCT;
	float3 ambientColor;
	float  ambientIntensity;
	float3 directionalColor;
	float  directionalIntensity;
	float3 direction;
	float  padding0;
};

struct PointLight {
	SHARED_STRUCT;
	float3 color;
	float  intensity;
	float3 position;
	float  range;
	float4 viewSpacePosition;
};

struct SpotLight {
	SHARED_STRUCT;
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
	SHARED_STRUCT;
	uint numPointLights;
	uint pointLightIndices[MAX_TILE_POINT_LIGHT_NUM];
	uint numSpotLights;
	uint spotLightIndices[MAX_TILE_POINT_LIGHT_NUM];
};

#endif
