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

	_lookFrom = desc.lookFrom;
	_lookUp = v.xyz;
	_lookAt = desc.lookAt;
	_nearClip = desc.nearClip;
	_farClip = desc.farClip;
	_fov = desc.fov;
	_aspect = desc.aspect;

	assert(lengthSquare(Vector3(_lookUp)) > 0.f);
	assert(lengthSquare(w) > 0.f);
	assert(_fov > 1.f);
	assert(_nearClip > 0.f);
	assert(_farClip > _nearClip);
}

const Math::float4x4 &Camera::getView() const {
	return _matView;
}

const Math::float4x4 &Camera::getProj() const {
	return _matProj;
}

const Math::float4x4 &Camera::getViewProj() const {
	return _matViewProj;
}

const Math::float4x4 &Camera::getInvView() const {
	return _matInvView;
}

const Math::float4x4 &Camera::getInvProj() const {
	return _matInvProj;
}

const Math::float4x4 &Camera::getInvViewProj() const {
	return _matInvViewProj;
}

void Camera::update() {
	Vector3 lookFrom(_lookFrom);
	Vector3 lookAt(_lookAt);
	Vector3 lookUp(_lookUp);
	Matrix4 view = DirectX::XMMatrixLookAtLH(lookFrom, lookAt, lookUp);
	Matrix4 proj = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(_fov),
		_aspect,
		_nearClip,
		_farClip
	);
	Matrix4 viewProj = proj * view;

	Matrix4 invView = inverse(view);
	Matrix4 invProj = inverse(proj);
	Matrix4 invViewProj = inverse(viewProj);

	_matView = float4x4(view);
	_matProj = float4x4(proj);
	_matViewProj = float4x4(viewProj);
	_matInvView = float4x4(invView);
	_matInvProj = float4x4(invProj);
	_matInvViewProj = float4x4(invViewProj);
	_projSpaceFrustum = { proj };
	_viewSpaceFrustum = _projSpaceFrustum.transform(invView);
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
	_lookFrom = lookFrom;
}

void Camera::setLookUp(const Math::float3 &lookUp) {
	_lookUp = lookUp;
}

void Camera::setLookAt(const Math::float3 &lookAt) {
	_lookAt = lookAt;
}

void Camera::setFov(float fov) {
	_fov = std::clamp(fov, 1.f, 89.f);
}

void Camera::setAspect(float aspect) {
	_aspect = aspect;
}

auto Camera::getLookFrom() const -> const Math::float3 & {
	return _lookFrom;
}

auto Camera::getLookUp() const -> const Math::float3 & {
	return _lookUp;
}

auto Camera::getLookAt() const -> const Math::float3 & {
	return _lookAt;
}

float Camera::getFov() const {
	return _fov;
}

float Camera::getAspect() const {
	return _aspect;
}

const BoundingFrustum &Camera::getProjSpaceFrustum() const {
	return _projSpaceFrustum;
}

const BoundingFrustum &Camera::getViewSpaceFrustum() const {
	return _viewSpaceFrustum;
}

}