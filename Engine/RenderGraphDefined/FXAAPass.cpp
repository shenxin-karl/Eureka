#include "FXAAPass.h"
#include "HlslShader/ShaderManager.h"
#include "ShaderHelper/GraphicsShader.h"
#include "Model/MeshManager.h"
#include "Defined/EngineDefined.h"
#include "Model/GeometryGenerator/GeometryGenerator.h"

namespace Eureka {

FXAAPass::FXAAPass(const std::string &passName, dx12lib::IDirectContext &directCtx)
: GraphicsPass(passName)
, pBackBuffer(this, "BackBuffer")
, pScreenMap(this, "ScreenMap")
{
	pFXAAPso = ShaderManager::instance()->getGraphicsShader("FXAA")->getPSO();
	rgph::ShaderLayoutMask mask = rgph::ShaderLayoutMask::Position | rgph::ShaderLayoutMask::TexCoord0;

	auto pMesh = GeometryGenerator::instance()->createQuad(-1.f, -1.f, 2.f, 2.f, 0.f);
	pFullScreenGeometry = GeometryGenerator::instance()->createGeometry(directCtx, mask, pMesh);
}

void FXAAPass::execute(dx12lib::DirectContextProxy pDirectCtx) {
	GraphicsPass::execute(pDirectCtx);

	pDirectCtx->setGraphicsPSO(pFXAAPso);
	pDirectCtx->setConstantBufferView("FXAASetting", pCbFXAASetting->getCBV());
	pDirectCtx->setShaderResourceView("gScreenMap", pScreenMap->get2dSRV());
	auto mask = rgph::ShaderLayoutMask::Position | rgph::ShaderLayoutMask::TexCoord0;
	pFullScreenGeometry->bind(*pDirectCtx, mask);
	pFullScreenGeometry->draw(*pDirectCtx);
}

void FXAAPass::setViewportScissorRect(dx12lib::IGraphicsContext &graphicsCtx) {
	graphicsCtx.setViewport(pScreenMap->getViewport());
	graphicsCtx.setScissorRect(pScreenMap->getScissorRect());
}

void FXAAPass::setRenderTargets(dx12lib::IGraphicsContext &graphicsContext) {
	graphicsContext.setRenderTarget(pBackBuffer->get2dRTV());
}

}
