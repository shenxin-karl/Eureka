#include "FXAAPass.h"
#include "HlslShader/ShaderManager.h"
#include "ShaderHelper/GraphicsShader.h"
#include "Model/MeshManager.h"
#include "Defined/EngineDefined.h"

namespace Eureka {

FXAAPass::FXAAPass(const std::string &passName)
: GraphicsPass(passName)
, pBackBuffer(this, "BackBuffer")
, pScreenMap(this, "ScreenMap")
{
	pFXAAPso = ShaderManager::instance()->getGraphicsShader("FXAA")->getPSO();
}

void FXAAPass::execute(dx12lib::DirectContextProxy pDirectCtx) {
	GraphicsPass::execute(pDirectCtx);

	auto pPositionVertBuffer = MeshManager::instance()->getVertexBuffer(kEurekaFullScreen_POSITION);
	auto pTexcoordVertBuffer = MeshManager::instance()->getVertexBuffer(kEurekaFullScreen_TEXCOORD);
}

void FXAAPass::setViewportScissorRect(dx12lib::IGraphicsContext &graphicsCtx) {
	graphicsCtx.setViewport(pScreenMap->getViewport());
	graphicsCtx.setScissorRect(pScreenMap->getScissorRect());
}

void FXAAPass::setRenderTargets(dx12lib::IGraphicsContext &graphicsContext) {
	graphicsContext.setRenderTarget(pBackBuffer->get2dRTV());
}

}
