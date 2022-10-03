#include "EurekaApplication.h"
#include "InputSystem/InputSystem.h"
#include "InputSystem/window.h"
#include <dx12lib/Device/DeviceStd.h>
#include <dx12lib/Context/ContextStd.h>
#include "GameTimer/GameTimer.h"
#include "Dx12lib/Texture/Texture.h"
#include "Model/MeshManager.h"
#include "ShaderHelper/GraphicsShader.h"

using namespace Math;

namespace Eureka {

void EurekaApplication::onInitialize(dx12lib::DirectContextProxy pDirectCtx) {
	MeshManager::SingletionEmplace();

	auto pShader = std::make_unique<GraphicsShader>(_pDevice, "Engine/HlslShader/ForwardPBR.hlsl");
	pShader->setVertexShader("VS");
	pShader->setPixelShader("PS");
	pShader->getPSO({});
}

void EurekaApplication::onDestroy() {
	MeshManager::SingletionDestory();
}

void EurekaApplication::onBeginTick(std::shared_ptr<GameTimer> pGameTimer) {
}

void EurekaApplication::onTick(std::shared_ptr<GameTimer> pGameTimer) {
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

	D3D12_RECT scissorRect{
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

void EurekaApplication::onEndTick(std::shared_ptr<GameTimer> pGameTimer) {
	auto pCmdQueue = _pDevice->getCommandQueue();
	pCmdQueue->signal(_pSwapChain);
}

void EurekaApplication::onResize(dx12lib::DirectContextProxy pDirectCtx, int width, int height) {

}

}