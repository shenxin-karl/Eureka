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
	Math::float4   gLightDirection;
	Math::float4   gLightRadiance;
	Math::float4x4 gProj;
	Math::float3   gCameraPosition;
	float		   gWidth;
	Math::float3   gViewLeftTop;
	float		   gHeight;
	Math::float3   gViewDownDir;
	float		   padding0;
	Math::float3   gViewRightDir;
	float		   padding1;
};

}

