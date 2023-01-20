#include <algorithm>
#include <iostream>
#include "Camera.h"
#include "Foundation/GameTimer.h"
#include "InputSystem/Mouse.h"
#include "InputSystem/Keyboard.h"


namespace Eureka {

using namespace Math;

Camera::Camera(const CameraDesc &desc) {
	Vector3 w = normalize(Vector3(desc.lookAt) - Vector3(desc.lookFrom));
	Vector3 u = normalize(cross(Vector3(desc.lookUp), w));
	Vector3 v = cross(w, u);

	_cameraData.lookFrom = desc.lookFrom;
	_cameraData.lookUpDir = v.xyz.store();
	_cameraData.lookAtDir = desc.lookAt;
	_cameraData.zNear = desc.nearClip;
	_cameraData.zFar = desc.farClip;
	_cameraData.fov = desc.fov;
	_cameraData.aspect = desc.aspect;

	assert(lengthSquare(Vector3(_cameraData.lookUpDir)) > 0.f);
	assert(lengthSquare(w) > 0.f);
	assert(_cameraData.fov > 1.f);
	assert(_cameraData.zNear> 0.f);
	assert(_cameraData.zFar > _cameraData.zNear);
}

const Math::float4x4 &Camera::getView() const {
	return _cameraData.matView;
}

const Math::float4x4 &Camera::getProj() const {
	return _cameraData.matProj;
}

const Math::float4x4 &Camera::getViewProj() const {
	return _cameraData.matViewProj;
}

const Math::float4x4 &Camera::getInvView() const {
	return _cameraData.matInvView;
}

const Math::float4x4 &Camera::getInvProj() const {
	return _cameraData.matInvProj;
}

const Math::float4x4 &Camera::getInvViewProj() const {
	return _cameraData.matInvViewProj;
}

const Math::float4x4 & Camera::getMatPreviousViewProj() const {
	return _cameraData.matPreviousViewProj;
}

void Camera::update() {
	Vector3 lookFrom(_cameraData.lookFrom);
	Vector3 lookAt(_cameraData.lookAtDir);
	Vector3 lookUp(_cameraData.lookUpDir);
	Matrix view = Matrix::CreateLookAt(lookFrom, lookFrom + lookAt, lookUp);
	Matrix proj = Matrix::CreatePerspectiveFieldOfView(
		DirectX::XMConvertToRadians(_cameraData.fov),
		_cameraData.aspect,
		_cameraData.zNear,
		_cameraData.zFar
	);
	Matrix viewProj = proj * view;

	Matrix invView = inverse(view);
	Matrix invProj = inverse(proj);
	Matrix invViewProj = inverse(viewProj);


	_cameraData.matPreviousViewProj = _cameraData.matViewProj;

	_cameraData.matView = float4x4(view);
	_cameraData.matProj = float4x4(proj);
	_cameraData.matViewProj = float4x4(viewProj);
	_cameraData.matInvView = float4x4(invView);
	_cameraData.matInvProj = float4x4(invProj);
	_cameraData.matInvViewProj = float4x4(invViewProj);
	_cameraData.projSpaceFrustum = Math::BoundingFrustum(proj);
	_cameraData.viewSpaceFrustum = _cameraData.projSpaceFrustum.transform(invView);
}

Matrix Camera::getMatView() const {
	return Matrix(getView());
}

Matrix Camera::getMatProj() const {
	return Matrix(getProj());
}

Matrix Camera::getMatViewProj() const {
	return Matrix(getViewProj());
}

Matrix Camera::getMatInvView() const {
	return Matrix(getInvView());
}

Matrix Camera::getMatInvProj() const {
	return Matrix(getInvProj());
}

Matrix Camera::getMatInvViewProj() const {
	return Matrix(getInvViewProj());
}

void Camera::setLookFrom(const Math::float3 &lookFrom) {
	_cameraData.lookFrom = lookFrom;
}

void Camera::setLookUp(const Math::float3 &lookUp) {
	_cameraData.lookUpDir = lookUp;
}

void Camera::setLookAt(const Math::float3 &lookAt) {
	_cameraData.lookAtDir = lookAt;
}

void Camera::setFov(float fov) {
	_cameraData.fov = std::clamp(fov, 1.f, 89.f);
}

void Camera::setAspect(float aspect) {
	_cameraData.aspect = aspect;
}

auto Camera::getLookFrom() const -> const Math::float3 & {
	return _cameraData.lookFrom;
}

auto Camera::getLookUp() const -> const Math::float3 & {
	return _cameraData.lookUpDir;
}

auto Camera::getLookAt() const -> const Math::float3 & {
	return _cameraData.lookAtDir;
}

auto Camera::getNearClip() const -> float {
	return _cameraData.zNear;
}

auto Camera::getFarClip() const -> float {
	return _cameraData.zFar;
}

float Camera::getFov() const {
	return _cameraData.fov;
}

float Camera::getAspect() const {
	return _cameraData.aspect;
}

const BoundingFrustum &Camera::getProjSpaceFrustum() const {
	return _cameraData.projSpaceFrustum;
}

const BoundingFrustum &Camera::getViewSpaceFrustum() const {
	return _cameraData.viewSpaceFrustum;
}

auto Camera::getCameraData() const -> const rgph::CameraData & {
	return _cameraData;
}

}
