#pragma once
#include <Math/MathStd.hpp>

namespace Eureka {

#define CBUFFER struct alignas(16)

CBUFFER CbPrePass {
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
	float          fogStart;
    float          fogEnd;
    Math::float4   fogColor;						

	// TAA
    Math::float4x4 gMatJitterViewProj;
	Math::float4x4 gMatViewport;
    Math::float4x4 gMatPreViewport;
};

CBUFFER CbPreObject {
    Math::float4x4 matWorld;
    Math::float4x4 matInvWorld;
    Math::float4x4 matNormal;
    Math::float4x4 matInvNormal;
};

CBUFFER FXAASetting {
    float minThreshold          = 0.0312f;
    float threshold             = 0.125f;
    float consoleTangentScale   = 0.5f;
    float sharpness             = 8.f;
};

struct DirectionalLight {
	Math::float3	ambientColor;
	float			ambientIntensity;
	Math::float3	directionalColor;
	float			directionalIntensity;
	Math::float3	direction;
	float			padding0;
};

CBUFFER CbLighting {
	DirectionalLight gDirectionalLight;
	Math::float4x4   gInvViewProj;
	Math::float3     gCameraPosition;
	float            gClosedIntervalOfHeight;       // height - 1
	float            gClosedIntervalOfWidth;        // width - 1
};

struct PointLight {
	Math::float3	color;
	float			intensity;
	Math::float3	position;
	float			range;
};

struct SpotLight {
	Math::float3	color;
	float			intensity;
	Math::float3	position;
	float			range;
	Math::float3    direction;
	float			boundingSphereRadius;
	Math::float3    viewSpaceBoundingSphereCenter;
	float			innerConeCosTheta;
	float			outerConeCosTheta;
};

#define MAX_TILE_POINT_LIGHT_NUM	160
#define MAX_TILE_SPOT_LIGHT_NUM		160
#define TBDR_TILE_DIMENSION			16
#define TBDR_TILE_SIZE				(TBDR_TILE_DIMENSION * TBDR_TILE_DIMENSION)

struct LightList {
	uint32_t numPointLights;
	uint32_t pointLightIndices[MAX_TILE_POINT_LIGHT_NUM];
	uint32_t numSpotLights;
	uint32_t spotLightIndices[MAX_TILE_SPOT_LIGHT_NUM];
};

}

