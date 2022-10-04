#include <RenderGraph/Pass/ClearPass.hpp>
#include <RenderGraph/RenderGraph/RenderGraph.h>
#include <RenderGraph/Pass/PresentPass.hpp>
#include <Dx12lib/Device/SwapChain.h>
#include "RenderGraph.h"
#include "Application/EurekaApplication.h"

namespace Eureka {

std::shared_ptr<rgph::RenderGraph> SetupRenderGraph(EurekaApplication *pApp) {
	auto pRenderGraph = std::make_shared<rgph::RenderGraph>();
	
	auto pClearBackBuffer = std::make_shared<rgph::ClearPass>("ClearBackBuffer");
	{
		auto getRenderTarget = [&]() { return pApp->getSwapChain()->getRenderTarget2D(); };
		auto getDepthStencil = [&]() { return pApp->getSwapChain()->getDepthStencil2D(); };
		getRenderTarget >> pClearBackBuffer->pRenderTarget;
		getDepthStencil >> pClearBackBuffer->pDepthStencil;
		pRenderGraph->addPass(pClearBackBuffer);
	}

	auto pPresentPass = std::make_shared<rgph::PresentPass>("PrensentPass");
	{
		pPresentPass->pRenderTarget.preExecuteState = D3D12_RESOURCE_STATE_PRESENT;
		pClearBackBuffer->pRenderTarget >> pPresentPass->pRenderTarget;
	}
	return pRenderGraph;
}

}