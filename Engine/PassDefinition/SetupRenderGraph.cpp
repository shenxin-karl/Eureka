#include <RenderGraph/Pass/ClearPass.hpp>
#include <RenderGraph/RenderGraph/RenderGraph.h>
#include <RenderGraph/Pass/PresentPass.hpp>
#include <Dx12lib/Device/SwapChain.h>
#include "PassDefinition/SetupRenderGraph.h"

#include "ClusterDeferredPass.h"
#include "CopyToBackPass.h"
#include "FXAAPass.h"
#include "GBufferPass.h"
#include "LightingPass.h"
#include "PostProcessingPass.h"
#include "TemporalAAPass.h"
#include "TileDeferredPass.h"
#include "Application/EurekaApplication.h"

namespace Eureka {

std::shared_ptr<rgph::RenderGraph> SetupRenderGraph(EurekaApplication *pApp, dx12lib::IDirectContext &directCtx) {
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
	auto pClearVelocity = std::make_shared<rgph::ClearRtPass>("ClearVelocityMa");
	{
		pApp->pVelocityMap >> pClearVelocity->pRenderTarget2d;
		pRenderGraph->addPass(pClearVelocity);
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

		pClearVelocity->pRenderTarget2d >> pGBufferPass->pVelocityMap;
		pGBufferPass->pVelocityMap.preExecuteState = D3D12_RESOURCE_STATE_RENDER_TARGET;

		pRenderGraph->addPass(pGBufferPass);
	}

	size_t numPointLights = pApp->pPointLightList->getElementCount();
	//auto pClusterDeferred = std::make_shared<ClusterDeferredPass>(kClusterDeferredPassName, directCtx, numPointLights);
	//{
	//	pClusterDeferred->pTileLightLists.preExecuteState = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
	//	pApp->pTileClusterLightList >> pClusterDeferred->pTileLightLists;

	//	pClusterDeferred->pPointLightLists.preExecuteState = D3D12_RESOURCE_STATE_GENERIC_READ;
	//	pApp->pPointLightList >> pClusterDeferred->pPointLightLists;

	//	pRenderGraph->addPass(pClusterDeferred);
	//}

	auto pTileDeferred = std::make_shared<TileDeferredPass>(kTileDeferredPassName, directCtx, numPointLights);
	{
		pTileDeferred->pDepthMap.preExecuteState = D3D12_RESOURCE_STATE_DEPTH_READ;
		pGBufferPass->pDepthStencil >> pTileDeferred->pDepthMap;

		pTileDeferred->pPointLightLists.preExecuteState = D3D12_RESOURCE_STATE_GENERIC_READ;
		pApp->pPointLightList >> pTileDeferred->pPointLightLists;

		pTileDeferred->pTileLightLists.preExecuteState = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
		pApp->pTileLightLists >> pTileDeferred->pTileLightLists;
		pRenderGraph->addPass(pTileDeferred);
	}

	auto pLightingPass = std::make_shared<LightingPass>(kLightingPassName, pApp->getDevice());
	{
		pLightingPass->pGBuffer0.preExecuteState = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
		pGBufferPass->pGBuffer0 >> pLightingPass->pGBuffer0;

		pLightingPass->pGBuffer1.preExecuteState = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
		pGBufferPass->pGBuffer1 >> pLightingPass->pGBuffer1;

		pLightingPass->pGBuffer2.preExecuteState = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
		pGBufferPass->pGBuffer2 >> pLightingPass->pGBuffer2;

		pLightingPass->pDepthMap.preExecuteState = D3D12_RESOURCE_STATE_DEPTH_READ;
		pGBufferPass->pDepthStencil >> pLightingPass->pDepthMap;
	
		pLightingPass->pLightingBuffer.preExecuteState = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
		pApp->pLightingBuffer >> pLightingPass->pLightingBuffer;

		pLightingPass->pCbLighting = pApp->pCbLighting;

		pLightingPass->pPointLightLists.preExecuteState = D3D12_RESOURCE_STATE_GENERIC_READ;
		pApp->pPointLightList >> pLightingPass->pPointLightLists;

		pLightingPass->pTileLightLists.preExecuteState = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
		pTileDeferred->pTileLightLists >> pLightingPass->pTileLightLists;

		pRenderGraph->addPass(pLightingPass);
	}

	auto pTemporalAAPass = std::make_shared<TemporalAAPass>(kTemporalAAPassName, directCtx);
	{
		pTemporalAAPass->pScreenMap.preExecuteState = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
		pLightingPass->pLightingBuffer >> pTemporalAAPass->pScreenMap;

		pTemporalAAPass->pOutputMap.preExecuteState = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
		pApp->pTemporalOutput >> pTemporalAAPass->pOutputMap;

		pRenderGraph->addPass(pTemporalAAPass);
	}

	auto pPostProcessingPass = std::make_shared<PostProcessingPass>(kPostProcessingPassName);
	{
		pPostProcessingPass->pScreenMap.preExecuteState = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
		pTemporalAAPass->pOutputMap >> pPostProcessingPass->pScreenMap;

		auto getBuffer = [=]() { return pApp->pPostProcessingBuffer; };
		pPostProcessingPass->pOutputMap.preExecuteState = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
		getBuffer >> pPostProcessingPass->pOutputMap;

		if (pApp->pColorLutMap != nullptr)
			pPostProcessingPass->setColorLutMap(pApp->pColorLutMap);
		pRenderGraph->addPass(pPostProcessingPass);
	}

	auto pCopyToBackPass = std::make_shared<CopyToBackPass>("CopyToBackPass", directCtx);
	{
		pCopyToBackPass->pScreenMap.preExecuteState = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
		pPostProcessingPass->pOutputMap >> pCopyToBackPass->pScreenMap;

		pCopyToBackPass->pBackBufferMap.preExecuteState = D3D12_RESOURCE_STATE_RENDER_TARGET;
		pClearBackBuffer->pRenderTarget2d >> pCopyToBackPass->pBackBufferMap;

		pRenderGraph->addPass(pCopyToBackPass);
	}

	auto pPresentPass = std::make_shared<rgph::PresentPass>("PresentPass");
	{
		pCopyToBackPass->pBackBufferMap >> pPresentPass->pBackBuffer;
		pRenderGraph->addPass(pPresentPass);
	}

	pRenderGraph->finalize();
	return pRenderGraph;
}

}
