#include <RenderGraph/Pass/ClearPass.hpp>
#include <RenderGraph/RenderGraph/RenderGraph.h>
#include <RenderGraph/Pass/PresentPass.hpp>
#include <Dx12lib/Device/SwapChain.h>
#include <RenderGraph/Pass/CopyPass.hpp>
#include "RenderGraphDefined/RenderGraphDefined.h"
#include "Application/EurekaApplication.h"

namespace Eureka {

GBufferPass::GBufferPass(const std::string &passName)
: RenderQueuePass(passName)
, pGBuffer0(this, "GBuffer0")
, pGBuffer1(this, "GBuffer1")
, pGBuffer2(this, "GBuffer2")
, pDepthStencil(this, "DepthStencil")
{
}

void GBufferPass::setViewportScissorRect(dx12lib::IGraphicsContext &graphicsCtx) {
	graphicsCtx.setViewport(pGBuffer0->getViewport());
	graphicsCtx.setScissorRect(pGBuffer0->getScissorRect());
}

void GBufferPass::setRenderTargets(dx12lib::IGraphicsContext &graphicsContext) {
	std::vector<dx12lib::RenderTargetView> rtvs;
	rtvs.push_back(pGBuffer0->get2dRTV());
	rtvs.push_back(pGBuffer1->get2dRTV());
	rtvs.push_back(pGBuffer2->get2dRTV());
	graphicsContext.setRenderTargets(rtvs, pDepthStencil->get2dDSV());
}

std::shared_ptr<rgph::RenderGraph> SetupRenderGraph(EurekaApplication *pApp) {
	auto pRenderGraph = std::make_shared<rgph::RenderGraph>();
	
	auto pClearBackBuffer = std::make_shared<rgph::ClearPass>("ClearBackBuffer");
	{
		auto getRenderTarget = [&]() { return pApp->getSwapChain()->getRenderTarget2D(); };
		auto getDepthStencil = [&]() { return pApp->getSwapChain()->getDepthStencil2D(); };
		getRenderTarget >> pClearBackBuffer->pRenderTarget2d;
		getDepthStencil >> pClearBackBuffer->pDepthStencil2d;
		pRenderGraph->addPass(pClearBackBuffer);
	}

	auto pClearGBuffer0 = std::make_shared<rgph::ClearRtPass>("ClearGBuffer0");
	{
		pApp->_pGBuffer0 >> pClearGBuffer0->pRenderTarget2d;
		pRenderGraph->addPass(pClearGBuffer0);
	}
	auto pClearGBuffer1 = std::make_shared<rgph::ClearRtPass>("ClearGBuffer1");
	{
		pApp->_pGBuffer0 >> pClearGBuffer1->pRenderTarget2d;
		pRenderGraph->addPass(pClearGBuffer1);
	}
	auto pClearGBuffer2 = std::make_shared<rgph::ClearRtPass>("ClearGBuffer2");
	{
		pApp->_pGBuffer0 >> pClearGBuffer2->pRenderTarget2d;
		pRenderGraph->addPass(pClearGBuffer2);
	}

	auto pGBufferPass = std::make_shared<GBufferPass>(kGBufferPassName);
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

	auto pCopyToBack = std::make_shared<rgph::CopyPass>("CopyToMainPass");
	{
		pClearBackBuffer->pRenderTarget2d >> pCopyToBack->pDstResource;
		pGBufferPass->pGBuffer0 >> pCopyToBack->pSrcResource;
		pRenderGraph->addPass(pCopyToBack);
	}

	auto pPresentPass = std::make_shared<rgph::PresentPass>("PresentPass");
	{
		pCopyToBack->pDstResource >> pPresentPass->pBackBuffer;
		pRenderGraph->addPass(pPresentPass);
	}

	pRenderGraph->finalize();
	return pRenderGraph;
}

}
