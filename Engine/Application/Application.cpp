#include "Application.h"
#include "InputSystem/InputSystem.h"
#include "InputSystem/window.h"
#include <dx12lib/Device/DeviceStd.h>
#include <dx12lib/Context/ContextStd.h>
#include "GameTimer/GameTimer.h"
#include "Dx12lib/Texture/Texture.h"
#include "MaterialSystem/Shader.h"

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

void Application::onInitialize(dx12lib::DirectContextProxy pDirectCtx) {
	auto pShader = std::make_unique<Eureka::Shader>(_pDevice, "Engine/HlslShader/ForwardPBRMeta.lua");
	auto *pShaderVariant = pShader->getShaderVariant({});
}

void Application::onDestroy() {
}

void Application::onBeginTick(std::shared_ptr<GameTimer> pGameTimer) {
}

void Application::onTick(std::shared_ptr<GameTimer> pGameTimer) {
	auto pCmdQueue = _pDevice->getCommandQueue();
	auto pDirectProxy = pCmdQueue->createDirectContextProxy();
	float cosine = std::cos(pGameTimer->getTotalTime());
	float sine = std::sin(pGameTimer->getTotalTime());
	float4 color = {
		cosine * 0.5f + 0.5f,
		sine * 0.5f + 0.5f,
		0.6f,
		1.f
	};

	D3D12_VIEWPORT viewport = {
		.TopLeftX = 0.f,
		.TopLeftY = 0.f,
		.Width = static_cast<float>(_width),
		.Height = static_cast<float>(_height),
		.MinDepth = 0.f,
		.MaxDepth = 1.f
	};

	D3D12_RECT scissorRect {
		.left = 0,
		.top = 0,
		.right = static_cast<LONG>(_width),
		.bottom = static_cast<LONG>(_height),
	};
	auto pRenderTarget2D = _pSwapChain->getRenderTarget2D();
	auto pDepthStencil2D = _pSwapChain->getDepthStencil2D();

	pDirectProxy->setViewport(viewport);
	pDirectProxy->setScissorRect(scissorRect);
	pDirectProxy->transitionBarrier(_pSwapChain->getRenderTarget2D(), D3D12_RESOURCE_STATE_RENDER_TARGET);
	{
		pDirectProxy->setRenderTarget(pRenderTarget2D->get2dRTV(), pDepthStencil2D->get2dDSV());
		pDirectProxy->clearColor(pRenderTarget2D->get2dRTV(), color);
	}
	pDirectProxy->transitionBarrier(pRenderTarget2D, D3D12_RESOURCE_STATE_PRESENT);
	pCmdQueue->executeCommandList(pDirectProxy);
}

void Application::onEndTick(std::shared_ptr<GameTimer> pGameTimer) {
	auto pCmdQueue = _pDevice->getCommandQueue();
	pCmdQueue->signal(_pSwapChain);
}

void Application::onResize(dx12lib::DirectContextProxy pDirectCtx, int width, int height) {
}

}
