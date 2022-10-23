#include "GraphicsPass.h"

namespace rgph {

GraphicsPass::GraphicsPass(const std::string &passName) : ExecutablePass(passName) {
}

void GraphicsPass::preExecute(dx12lib::IDirectContext &directCtx, const RenderView &view) {
	ExecutablePass::preExecute(directCtx, view);
}

void GraphicsPass::execute(dx12lib::IDirectContext &directCtx, const RenderView &view) {
	ExecutablePass::execute(directCtx, view);
	setViewportScissorRect(directCtx);
	setRenderTargets(directCtx);
}

void GraphicsPass::postExecute(dx12lib::IDirectContext &directCtx, const RenderView &view) {
	ExecutablePass::postExecute(directCtx, view);
}

PassType GraphicsPass::getPassType() const {
	return PassType::GraphicsPass;
}

}
