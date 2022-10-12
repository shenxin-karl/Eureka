#define NOMINMAX
#include <algorithm>
#include <iostream>
#include "Camera.h"
#include "GameTimer/GameTimer.h"
#include "InputSystem/Mouse.h"
#include "InputSystem/Keyboard.h"


namespace Eureka {

using namespace Math;

Camera::Camera(const CameraDesc &desc) {
	Vector3 w = normalize(Vector3(desc.lookAt) - Vector3(desc.lookFrom));
	Vector3 u = normalize(cross(Vector3(desc.lookUp), w));
	Vector3 v = cross(w, u);

	_cameraData.lookFrom = desc.lookFrom;
	_cameraData.lookUpDir = v.xyz;
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

void Camera::update() {
	Vector3 lookFrom(_cameraData.lookFrom);
	Vector3 lookAt(_cameraData.lookAtDir);
	Vector3 lookUp(_cameraData.lookUpDir);
	Matrix4 view = DirectX::XMMatrixLookAtLH(lookFrom, lookFrom + lookAt, lookUp);
	Matrix4 proj = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(_cameraData.fov),
		_cameraData.aspect,
		_cameraData.zNear,
		_cameraData.zFar
	);
	Matrix4 viewProj = proj * view;

	Matrix4 invView = inverse(view);
	Matrix4 invProj = inverse(proj);
	Matrix4 invViewProj = inverse(viewProj);

	_cameraData.matView = float4x4(view);
	_cameraData.matProj = float4x4(proj);
	_cameraData.matViewProj = float4x4(viewProj);
	_cameraData.matInvView = float4x4(invView);
	_cameraData.matInvProj = float4x4(invProj);
	_cameraData.matInvViewProj = float4x4(invViewProj);
	_cameraData.projSpaceFrustum = { proj };
	_cameraData.viewSpaceFrustum = _cameraData.projSpaceFrustum.transform(invView);
}

Matrix4 Camera::getMatView() const {
	return Matrix4(getView());
}

Matrix4 Camera::getMatProj() const {
	return Matrix4(getProj());
}

Matrix4 Camera::getMatViewProj() const {
	return Matrix4(getViewProj());
}

Matrix4 Camera::getMatInvView() const {
	return Matrix4(getInvView());
}

Matrix4 Camera::getMatInvProj() const {
	return Matrix4(getInvProj());
}

Matrix4 Camera::getMatInvViewProj() const {
	return Matrix4(getInvViewProj());
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
