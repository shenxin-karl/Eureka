#pragma once
#include <DirectXCollision.h>
#include "Math/MathHelper.h"
#include "Math/MathStd.hpp"
#include "RenderGraph/Utility/Utility.h"

namespace Eureka {

class GameTimer;
struct CameraDesc {
	Math::float3 lookFrom;
	Math::float3 lookUp;
	Math::float3 lookAt;
	float        fov;
	float        nearClip;
	float        farClip;
	float        aspect;
};

class Camera {
public:
	Camera(const CameraDesc &desc);
	const Math::float4x4 &getView() const;
	const Math::float4x4 &getProj() const;
	const Math::float4x4 &getViewProj() const;
	const Math::float4x4 &getInvView() const;
	const Math::float4x4 &getInvProj() const;
	const Math::float4x4 &getInvViewProj() const;
	const Math::float4x4 &getMatPreviousViewProj() const;
	void update();
	Math::Matrix4 getMatView() const;
	Math::Matrix4 getMatProj() const;
	Math::Matrix4 getMatViewProj() const;
	Math::Matrix4 getMatInvView() const;
	Math::Matrix4 getMatInvProj() const;
	Math::Matrix4 getMatInvViewProj() const;
	void setLookFrom(const Math::float3 &lookFrom);
	void setLookUp(const Math::float3 &lookUp);
	void setLookAt(const Math::float3 &lookAt);
	void setFov(float fov);
	void setAspect(float aspect);
	auto getLookFrom() const -> const Math::float3 &;
	auto getLookUp() const -> const Math::float3 &;
	auto getLookAt() const -> const Math::float3 &;
	auto getNearClip() const -> float;
	auto getFarClip() const -> float;
	float getFov() const;
	float getAspect() const;
	const Math::BoundingFrustum &getProjSpaceFrustum() const;
	const Math::BoundingFrustum &getViewSpaceFrustum() const;
	auto getCameraData() const -> const rgph::CameraData &;
private:
	rgph::CameraData _cameraData;
};

}
