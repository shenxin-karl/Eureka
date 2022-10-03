#include "Application.h"
#include "InputSystem/InputSystem.h"
#include "InputSystem/window.h"
#include <dx12lib/Device/DeviceStd.h>
#include <dx12lib/Context/ContextStd.h>
#include "GameTimer/GameTimer.h"

using namespace Math;

namespace Eureka {

void Application::initialize() {
	_pInputSystem = std::make_shared<InputSystem>(_title, _width, _height);
	_pInputSystem->initialize();
	_pInputSystem->pWindow->setResizeCallback([&](int width, int height) {
		resize(width, height);
	});

	_pAdapter = std::make_shared<dx12lib::Adapter>();
	_pDevice = std::make_shared<dx12lib::Device>(_pAdapter);

	dx12lib::DeviceInitDesc desc = {
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		_fps,
	};
	_pDevice->initialize(desc);

	_pSwapChain = _pDevice->createSwapChain(_pInputSystem->pWindow->getHWND());
	_pSwapChain->setVerticalSync(true);

	// first resize
	auto pCmdQueue = _pDevice->getCommandQueue();
	auto pDirectContext = pCmdQueue->createDirectContextProxy();
	_pSwapChain->resize(pDirectContext, _width, _height);
	onInitialize(pDirectContext);
	pCmdQueue->executeCommandList(pDirectContext);
	pCmdQueue->signal(_pSwapChain);
	pCmdQueue->flushCommandQueue();
}

void Application::destroy() {
	auto pCmdQueue = _pDevice->getCommandQueue();
	pCmdQueue->flushCommandQueue();
	onDestroy();
	_pInputSystem->destroy();
	_pDevice->destroy();
}

void Application::beginTick(std::shared_ptr<GameTimer> pGameTimer) {
	_pInputSystem->beginTick(pGameTimer);
	if (_canPause && _pInputSystem->pWindow->isPause()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000.f / 60.f)));
		return;
	}

	auto pCmdQueue = _pDevice->getCommandQueue();
	pCmdQueue->startNewFrame();		// start new frames
	onBeginTick(pGameTimer);
}

void Application::tick(std::shared_ptr<GameTimer> pGameTimer) {
	_pInputSystem->tick(pGameTimer);
	if (_canPause && _pInputSystem->pWindow->isPause())
		return;

	onTick(pGameTimer);
}

void Application::endTick(std::shared_ptr<GameTimer> pGameTimer) {
	_pInputSystem->endTick(pGameTimer);
	if (_canPause && _pInputSystem->pWindow->isPause())
		return;

	onEndTick(pGameTimer);
	_pDevice->releaseStaleDescriptor();
}

void Application::resize(int width, int height) {
	if (width == 0 || height == 0)
		return;

	_width = width;
	_height = height;
	auto pCmdQueue = _pDevice->getCommandQueue();
	pCmdQueue->flushCommandQueue();
	pCmdQueue->startNewFrame();
	auto pCmdList = pCmdQueue->createDirectContextProxy();
	_pSwapChain->resize(pCmdList, width, height);
	onResize(pCmdList, width, height);
	pCmdQueue->executeCommandList(pCmdList);
	pCmdQueue->signal(_pSwapChain);
	pCmdQueue->flushCommandQueue();
}

bool Application::isRunning() const {
	return !_pInputSystem->shouldClose();
}

}
