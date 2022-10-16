#pragma once
#include <Math/MathStd.hpp>
#include <Dx12lib/Pipeline/ShaderRegister.hpp>

namespace Eureka {

constexpr dx12lib::RegisterSpace kPrePassSpace = dx12lib::RegisterSpace::Space8;
constexpr dx12lib::RegisterSpace kPreObjectSpace = dx12lib::RegisterSpace::Space0;

struct alignas(16) CbPrePass {
    /// camera
	Math::float4x4 matView;
	Math::float4x4 matInvView;
	Math::float4x4 matProj;
	Math::float4x4 matInvProj;
	Math::float4x4 matViewProj;
	Math::float4x4 matInvViewProj;
	Math::float3   cameraPos;
	float		   nearClip;
    Math::float3   cameraLookUp;
	float		   farClip;
    Math::float3   cameraLookAt;
	float		   cbPrePassPadding0;

    /// RenderTarget
	Math::float2   renderTargetSize;
	Math::float2   invRenderTargetSize;

    /// time
	float		   totalTime;
	float		   deltaTime;

    /// fog
    Math::float4   fogColor;						
	float          fogStart;
    float          fogEnd;
    Math::float2   cbPrePassPadding1;
};

struct alignas(16) CbPreObject {
    Math::float4x4 matWorld;
    Math::float4x4 matInvWorld;
    Math::float4x4 matNormal;
    Math::float4x4 matInvNormal;
};

struct alignas(16) FXAASetting {
    float minThreshold          = 0.0312f;
    float threshold             = 0.125f;
    float consoleTangentScale   = 0.5f;
    float sharpness             = 8.f;
};

struct alignas(16) CbLighting {
	Math::float3    gLightDirection;                // 向着光源
    float           gClosedIntervalOfWidth;         // width - 1
	Math::float3    gLightRadiance;
    float           gClosedIntervalOfHeight;        // height - 1
	Math::float4x4  gInvViewProj;
	Math::float3    gCameraPosition;
    float           padding0;
};

struct DirectionalLight {
	Math::float3	ambientColor;
	float			ambientIntensity;
	Math::float3	directionalColor;
	float			directionalIntensity;
	Math::float3	direction;
	float			padding0;
};

struct PointLight {
	Math::float3	color;
	float			intensity;
	Math::float3	position;
	float			range;
	Math::float4	viewSpacePosition;
};

struct SpotLight {
	Math::float3	color;
	float			intensity;
	Math::float3	position;
	float			range;
};

#define MAX_TILE_POINT_LIGHT_NUM	80
#define MAX_TILE_SPOT_LIGHT_NUM		80
#define TBDR_TILE_DIMENSION			16
#define TBDR_TILE_SIZE				(TBDR_TILE_DIMENSION * TBDR_TILE_DIMENSION)

struct LightList {
	uint32_t numPointLights;
	uint32_t pointLightIndices[MAX_TILE_POINT_LIGHT_NUM];
	uint32_t numSpotLights;
	uint32_t spotLightIndices[MAX_TILE_POINT_LIGHT_NUM];
};

}

