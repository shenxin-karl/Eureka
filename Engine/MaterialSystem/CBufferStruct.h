#pragma once
#include <Math/MathStd.hpp>
#include <Dx12lib/Pipeline/ShaderRegister.hpp>

namespace Eureka {

constexpr dx12lib::RegisterSpace kPrePassSpace = dx12lib::RegisterSpace::Space8;
constexpr dx12lib::RegisterSpace kPreObjectSpace = dx12lib::RegisterSpace::Space0;

struct CbPrePass {
    // camera
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
    Math::float4   cameraLookAt;

    // RenderTarget
	Math::float2   renderTargetSize;
	Math::float2   invRenderTargetSize;

    /// time
	float		   totalTime;
	float		   deltaTime;

    /// fog
    Math::float4   fogColor;						
	float          fogStart;
    float          fogEnd;
    Math::float2   cbPerPassPad1;

	constexpr static dx12lib::ShaderRegister kShaderRegister{
		dx12lib::RegisterSlot::CBV8,
		kPrePassSpace
	};
};

struct CbPreObject {
    Math::float4x4 matWorld;
    Math::float4x4 matInvWorld;
    Math::float4x4 matNormal;
    Math::float4x4 matInvNormal;

	constexpr static dx12lib::ShaderRegister kShaderRegister{
		dx12lib::RegisterSlot::CBV8,
		kPreObjectSpace
	};
};

}

