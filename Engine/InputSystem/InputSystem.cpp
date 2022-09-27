#include "GameTimer/GameTimer.h"
#include "InputSystem/InputSystem.h"
#include "InputSystem/Window.h"
#include "InputSystem/Mouse.h"
#include "InputSystem/Keyboard.h"

namespace Eureka {

InputSystem::InputSystem(const std::string &title, int width, int height) {
	pWindow = std::make_unique<Window>(width, height, title, this);
	pMouse = std::make_unique<Mouse>(this);
	pKeyboard = std::make_unique<Keyboard>();
	pWindow->setMessageDispatchCallback([&](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		pMouse->handleMsg(hwnd, msg, wParam, lParam);
		pKeyboard->handleMsg(hwnd, msg, wParam, lParam);
	});
}

InputSystem::~InputSystem() {
}

bool InputSystem::shouldClose() const {
	return pWindow->shouldClose();
}


void InputSystem::beginTick(std::shared_ptr<GameTimer> pGameTimer) {
	pWindow->beginTick(pGameTimer);
	pMouse->beginTick(pGameTimer);
	pKeyboard->beginTick(pGameTimer);
}

void InputSystem::tick(std::shared_ptr<GameTimer> pGameTimer) {
	pWindow->tick(pGameTimer);
	pMouse->tick(pGameTimer);
	pKeyboard->tick(pGameTimer);
}


void InputSystem::endTick(std::shared_ptr<GameTimer> pGameTimer) {
	pWindow->endTick(pGameTimer);
	pMouse->endTick(pGameTimer);
	pKeyboard->endTick(pGameTimer);
}

}