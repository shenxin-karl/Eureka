#include "Application.h"
#include "InputSystem/InputSystem.h"
#include "InputSystem/Window.h"
#include <Dx12lib/Device/DeviceStd.h>
#include <Dx12lib/Context/ContextStd.h>
#include "Foundation/GameTimer.h"
#include "Foundation/Exception.h"
#include "EngineDefinition/EngineDefinition.h"

using namespace Math;

namespace Eureka {

void Application::Initialize(Application *pApplication) {
	Exception::Throw(_inst == nullptr, "Application::_inst is not nullptr!");
	_inst = pApplication;
	_inst->initialize();
}

void Application::BeginTick(std::shared_ptr<GameTimer> pGameTimer) {
	_inst->beginTick(std::move(pGameTimer));
}

void Application::Tick(std::shared_ptr<GameTimer> pGameTimer) {
	_inst->tick(std::move(pGameTimer));
}

void Application::EndTick(std::shared_ptr<GameTimer> pGameTimer) {
	_inst->endTick(std::move(pGameTimer));
}

void Application::Destroy() {
	_inst->destroy();
	delete _inst;
}

bool Application::IsRunning() {
	return !_inst->_pInputSystem->shouldClose();
}

auto Application::getDevice() -> const std::shared_ptr<dx12lib::Device> & {
	return _inst->_pDevice;
}

auto Application::getSwapChain() -> const std::shared_ptr<dx12lib::SwapChain> & {
	return _inst->_pSwapChain;
}

auto Application::getInputSystem() -> const std::shared_ptr<InputSystem> & {
	return _inst->_pInputSystem;
}

void Application::initialize() {
	_pInputSystem = std::make_shared<InputSystem>(_inst->_title, _inst->_width, _inst->_height);
	_pInputSystem->initialize();
	_pInputSystem->pWindow->setResizeCallback([&](int width, int height) {
		resize(width, height);
	});

	_pAdapter = std::make_shared<dx12lib::Adapter>();
	_pDevice = std::make_shared<dx12lib::Device>(_pAdapter);

	dx12lib::DeviceInitDesc desc = {
		kSwapChainRenderTargetFormat,
		kSwapChainDepthStencilFormat,
		_inst->_fps,
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

}
