#include "GraphicsPass.h"

namespace rgph {

GraphicsPass::GraphicsPass(const std::string &passName) : ExecutablePass(passName) {
}

void GraphicsPass::preExecute(dx12lib::DirectContextProxy pDirectCtx, const RenderView &view) {
	ExecutablePass::preExecute(pDirectCtx, view);
}

void GraphicsPass::execute(dx12lib::DirectContextProxy pDirectCtx, const RenderView &view) {
	ExecutablePass::execute(pDirectCtx, view);
	setViewportScissorRect(*pDirectCtx);
	setRenderTargets(*pDirectCtx);
}

void GraphicsPass::postExecute(dx12lib::DirectContextProxy pDirectCtx, const RenderView &view) {
	ExecutablePass::postExecute(pDirectCtx, view);
}

PassType GraphicsPass::getPassType() const {
	return PassType::GraphicsPass;
}

}
