#pragma once
#include <Math/MathStd.hpp>
#include <Dx12lib/Tool/RenderProfiler.hpp>

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

struct RenderView {
	CameraData cameraData;
	dx12lib::RenderProfiler *pProfiler;
};

}
