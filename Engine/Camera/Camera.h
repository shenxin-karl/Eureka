#pragma once
#include <DirectXCollision.h>
#include "Math/MathHelper.h"
#include "Math/MathStd.hpp"

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
	float getFov() const;
	float getAspect() const;
	const Math::BoundingFrustum &getProjSpaceFrustum() const;
	const Math::BoundingFrustum &getViewSpaceFrustum() const;
protected:
private:
	float  _fov;
	float  _aspect;
	Math::float3   _lookFrom;
	Math::float3   _lookUp;
	Math::float3   _lookAt;
	float          _nearClip;
	float          _farClip;
	Math::float4x4 _matView;
	Math::float4x4 _matInvView;
	Math::float4x4 _matProj;
	Math::float4x4 _matInvProj;
	Math::float4x4 _matViewProj;
	Math::float4x4 _matInvViewProj;
	Math::BoundingFrustum _viewSpaceFrustum;
	Math::BoundingFrustum _projSpaceFrustum;
};

}
