#include "Keyboard.h"

namespace Eureka {

Keyboard::Keyboard() {
}

bool Keyboard::isKeyPressed(unsigned char key) const {
	return _keyState.test(key);
}

bool Keyboard::isCharPressed(unsigned char key) const {
	return _characterState.test(key);
}

KeyEvent Keyboard::getKeyEvent() {
	if (_keycodeQueue.empty())
		return KeyEvent{};

	auto res = _keycodeQueue.front();
	_keycodeQueue.pop();
	return res;
}

CharEvent Keyboard::getCharEvent() {
	if (_characterQueue.empty())
		return CharEvent{};
	auto res = _characterQueue.front();
	_characterQueue.pop();
	return res;
}


void Keyboard::handleMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYDOWN:
		_keyState.set(wParam);
		_keycodeQueue.emplace(KeyState::Pressed, static_cast<char>(wParam));
		break;
	case WM_KEYUP:
		_keyState.set(wParam, false);
		_keycodeQueue.emplace(KeyState::Released, static_cast<char>(wParam));
		break;
	case WM_CHAR:
		_characterState.set(wParam);
		_characterQueue.emplace(KeyState::Pressed, static_cast<char>(wParam));
		break;
	}
}

void Keyboard::endTick(std::shared_ptr<GameTimer> pGameTimer) {
	tryDiscardEvent(_keycodeQueue);
	tryDiscardEvent(_characterQueue);
}

unsigned char KeyEvent::getKey() const {
	return _key;
}

KeyState KeyEvent::getState() const {
	return _state;
}

bool KeyEvent::isPressed() const {
	return _state == KeyState::Pressed;
}

bool KeyEvent::isReleased() const {
	return _state == KeyState::Released;
}

bool KeyEvent::isInvalid() const {
	return _state == KeyState::Invalid;
}

KeyEvent::operator bool() const {
	return !isInvalid();
}

KeyEvent::KeyEvent(KeyState state, unsigned char key) : _state(state), _key(key) {
}

unsigned char CharEvent::getCharacter() const {
	return _character;
}

KeyState CharEvent::getState() const {
	return _state;
}

bool CharEvent::isPressed() const {
	return _state == KeyState::Pressed;
}

bool CharEvent::isInvalid() const {
	return _state == KeyState::Invalid;
}

CharEvent::operator bool() const {
	return _state != KeyState::Invalid;
}

CharEvent::CharEvent(KeyState state, unsigned char character)
	: _state(state), _character(character) {
}

}