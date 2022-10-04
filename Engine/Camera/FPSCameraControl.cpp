#include "Camera.h"
#include "FPSCameraControl.h"
#include "InputSystem/InputSystem.h"
#include "InputSystem/Mouse.h"
#include "InputSystem/Keyboard.h"
#include "GameTimer/GameTimer.h"
#include "Math/MathStd.hpp"

using namespace Math;

namespace Eureka {

FPSCameraControl::FPSCameraControl(std::shared_ptr<Camera> pCamera) : _pCamera(std::move(pCamera)) {
	Vector3 lookAt = Vector3(_pCamera->getLookAt());
	Vector3 lookFrom = Vector3(_pCamera->getLookFrom());
	Vector3 lookUp = Vector3(_pCamera->getLookUp());
	Vector3 target = normalize(lookAt - lookFrom);
	Vector3 upDir = normalize(lookUp);
	_pitch = std::clamp(DirectX::XMConvertToDegrees(std::asin(target.y)), -89.9f, +89.9f);
	_yaw = DirectX::XMConvertToDegrees(std::atan2(target.z, target.x));
	_roll = DirectX::XMConvertToDegrees(std::asin(upDir.y));
}

void FPSCameraControl::update(std::shared_ptr<InputSystem> pInputSystem, std::shared_ptr<GameTimer> pGameTimer) {
	while (auto event = pInputSystem->pMouse->getEvent()) {
		if (event.isLPress()) {
			_mouseLeftPress = true;
			_lastMousePosition = POINT(event.x, event.y);
		} else if (event.isLRelease()) {
			_mouseLeftPress = false;
		}

		if (_lastMousePosition.x == -1 && _lastMousePosition.y == -1)
			_lastMousePosition = POINT(event.x, event.y);

		if (event._state == MouseState::Move) {
			float dx = static_cast<float>(event.x - _lastMousePosition.x) * mouseMoveSensitivity;
			float dy = static_cast<float>(event.y - _lastMousePosition.y) * mouseMoveSensitivity;
			setPitch(_pitch - dy);
			setYaw(_yaw - dx);
			_lastMousePosition = POINT(event.x, event.y);
		} else if (event._state == MouseState::Wheel) {
			float fovDeviation = event._offset * mouseWheelSensitivity;
			_pCamera->setFov(std::clamp(_pCamera->getFov() - fovDeviation, 1.f, 89.f));
		}
	}

	while (auto event = pInputSystem->pKeyboard->getKeyEvent()) {
		bool isPressed = event.getState() == KeyState::Pressed;
		switch (event.getKey()) {
		case 'W':
			_moveState[Forward] = isPressed;
			break;
		case 'S':
			_moveState[backward] = isPressed;
			break;
		case 'A':
			_moveState[Left] = isPressed;
			break;
		case 'D':
			_moveState[Right] = isPressed;
			break;
		case 'Q':
			_moveState[LeftRotate] = isPressed;
			break;
		case 'E':
			_moveState[RightRotate] = isPressed;
			break;
		}
	}

	float deltaTime = pGameTimer->getDeltaTime();
	float advance = 0.f;
	float deviation = 0.f;
	float rotate = 0.f;
	advance += static_cast<float>(_moveState[Forward]);
	advance -= static_cast<float>(_moveState[backward]);
	deviation += static_cast<float>(_moveState[Right]);
	deviation -= static_cast<float>(_moveState[Left]);
	rotate += static_cast<float>(_moveState[RightRotate]);
	rotate -= static_cast<float>(_moveState[LeftRotate]);

	Vector3 lookFrom = Vector3(_pCamera->getLookFrom());
	if (advance != 0.f || deviation != 0.f) {
		Vector3 lookAt = Vector3(_pCamera->getLookAt());
		Vector3 lookUp = Vector3(_pCamera->getLookUp());
		Vector3 w = normalize(lookAt - lookFrom);
		Vector3 u = cross(lookUp, w);
		Vector3 motor = normalize(w * advance + u * deviation) * (deltaTime * cameraMoveSpeed);
		lookFrom += motor;
		_pCamera->setLookFrom(lookFrom.xyz);
	}

	if (rotate != 0.f)
		_roll += rotate * rollSensitivity * deltaTime;

	float radianPitch = DirectX::XMConvertToRadians(_pitch);
	float radianYaw = DirectX::XMConvertToRadians(_yaw);
	float sinPitch = std::sin(radianPitch);
	float cosPitch = std::cos(radianPitch);
	float sinYaw = std::sin(radianYaw);
	float cosYaw = std::cos(radianYaw);
	Vector3 target = {
		cosPitch * cosYaw,
		sinPitch,
		cosPitch * sinYaw,
	};

	Vector3 lookAt = normalize(target) + lookFrom;
	float radianRoll = DirectX::XMConvertToRadians(_roll);
	float sinRoll = std::sin(radianRoll);
	float cosRoll = std::cos(radianRoll);
	Vector3 lookUp = Vector3(cosRoll, sinRoll, 0.f);

	_pCamera->setLookAt(lookAt.xyz);
	_pCamera->setLookUp(lookUp.xyz);
	_pCamera->update();
}

void FPSCameraControl::setPitch(float pitch) {
	_pitch = std::clamp(pitch, -89.9f, +89.9f);
}

void FPSCameraControl::setYaw(float yaw) {
	_yaw = yaw;
}

void FPSCameraControl::setRoll(float roll) {
	_roll = roll;
}

auto FPSCameraControl::getCamera() const -> std::shared_ptr<Camera> {
	return _pCamera;
}

}
