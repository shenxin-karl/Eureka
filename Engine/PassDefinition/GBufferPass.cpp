#include "GBufferPass.h"

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

}
