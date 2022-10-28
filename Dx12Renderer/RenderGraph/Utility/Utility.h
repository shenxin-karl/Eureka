#pragma once
#include <Math/MathStd.hpp>
#include <Dx12lib/Tool/RenderProfiler.hpp>
#include <Dx12lib/dx12libStd.h>

namespace rgph {

struct CameraData {
	float fov;
	float aspect;
	float zNear;
	float zFar;
	Math::float3 lookFrom;
	Math::float3 lookUpDir;			// y
	Math::float3 lookAtDir;			// z
	Math::float4x4	matView;
	Math::float4x4	matInvView;
	Math::float4x4  matProj;
	Math::float4x4  matInvProj;
	Math::float4x4	matViewProj;
	Math::float4x4  matInvViewProj;
	Math::BoundingFrustum viewSpaceFrustum;
	Math::BoundingFrustum projSpaceFrustum;
};

struct Viewport {
	size_t width;
	size_t height;
};

struct RenderView {
	Viewport viewport;
	uint64_t frameIndex = dx12lib::FrameIndexProxy::getConstantFrameIndexRef();
	float	 xJitter    = 0.f;
	float	 yJitter    = 0.f;
	CameraData cameraData;
	dx12lib::RenderProfiler *pProfiler;
};

}
