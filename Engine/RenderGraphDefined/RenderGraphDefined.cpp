#include <RenderGraph/Pass/ClearPass.hpp>
#include <RenderGraph/RenderGraph/RenderGraph.h>
#include <RenderGraph/Pass/PresentPass.hpp>
#include <Dx12lib/Device/SwapChain.h>
#include <RenderGraph/Pass/CopyPass.hpp>
#include "RenderGraphDefined/RenderGraphDefined.h"

#include "FXAAPass.h"
#include "Application/EurekaApplication.h"

namespace Eureka {

std::shared_ptr<rgph::RenderGraph> SetupRenderGraph(EurekaApplication *pApp) {
	auto pRenderGraph = std::make_shared<rgph::RenderGraph>();
	
	auto pClearBackBuffer = std::make_shared<rgph::ClearPass>("ClearBackBuffer");
	{
		auto getRenderTarget = [=]() { return pApp->getSwapChain()->getRenderTarget2D(); };
		auto getDepthStencil = [=]() { return pApp->getSwapChain()->getDepthStencil2D(); };
		getRenderTarget >> pClearBackBuffer->pRenderTarget2d;
		getDepthStencil >> pClearBackBuffer->pDepthStencil2d;
		pRenderGraph->addPass(pClearBackBuffer);
	}

	auto pClearGBuffer0 = std::make_shared<rgph::ClearRtPass>("ClearGBuffer0");
	{
		pApp->pGBuffer0 >> pClearGBuffer0->pRenderTarget2d;
		pRenderGraph->addPass(pClearGBuffer0);
	}
	auto pClearGBuffer1 = std::make_shared<rgph::ClearRtPass>("ClearGBuffer1");
	{
		pApp->pGBuffer1 >> pClearGBuffer1->pRenderTarget2d;
		pRenderGraph->addPass(pClearGBuffer1);
	}
	auto pClearGBuffer2 = std::make_shared<rgph::ClearRtPass>("ClearGBuffer2");
	{
		pApp->pGBuffer2 >> pClearGBuffer2->pRenderTarget2d;
		pRenderGraph->addPass(pClearGBuffer2);
	}

	
	auto pGBufferPass = std::make_shared<GBufferPass>(kGBufferPassName);
	pGBufferPass->setPassCBuffer(pApp->pCbPrePass);
	{
		pClearGBuffer0->pRenderTarget2d >> pGBufferPass->pGBuffer0;
		pGBufferPass->pGBuffer0.preExecuteState = D3D12_RESOURCE_STATE_RENDER_TARGET;
		pClearGBuffer1->pRenderTarget2d >> pGBufferPass->pGBuffer1;
		pGBufferPass->pGBuffer1.preExecuteState = D3D12_RESOURCE_STATE_RENDER_TARGET;
		pClearGBuffer2->pRenderTarget2d >> pGBufferPass->pGBuffer2;
		pGBufferPass->pGBuffer2.preExecuteState = D3D12_RESOURCE_STATE_RENDER_TARGET;
		pClearBackBuffer->pDepthStencil2d >> pGBufferPass->pDepthStencil;
		pGBufferPass->pDepthStencil.preExecuteState = D3D12_RESOURCE_STATE_DEPTH_WRITE;
		pRenderGraph->addPass(pGBufferPass);
	}

	auto pFXAAPass = std::make_shared<FXAAPass>("FXAAPass");
	{
		pGBufferPass->pGBuffer0 >> pFXAAPass->pScreenMap;
		pFXAAPass->pScreenMap.preExecuteState = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

		pClearBackBuffer->pRenderTarget2d >> pFXAAPass->pBackBuffer;
		pFXAAPass->pBackBuffer.preExecuteState = D3D12_RESOURCE_STATE_RENDER_TARGET;

		pFXAAPass->pCbFXAASetting = pApp->pCbFXAASetting;
		pRenderGraph->addPass(pFXAAPass);
	}

	auto pPresentPass = std::make_shared<rgph::PresentPass>("PresentPass");
	{
		pFXAAPass->pBackBuffer >> pPresentPass->pBackBuffer;
		pRenderGraph->addPass(pPresentPass);
	}

	pRenderGraph->finalize();
	return pRenderGraph;
}

}
