#include "GraphicsPass.h"

namespace rgph {

GraphicsPass::GraphicsPass(const std::string &passName) : ExecutablePass(passName) {
}

void GraphicsPass::preExecute(dx12lib::DirectContextProxy pDirectCtx) {
	ExecutablePass::preExecute(pDirectCtx);
}

void GraphicsPass::execute(dx12lib::DirectContextProxy pDirectCtx) {
	ExecutablePass::execute(pDirectCtx);
	setViewportScissorRect(*pDirectCtx);
	setRenderTargets(*pDirectCtx);
}

void GraphicsPass::postExecute(dx12lib::DirectContextProxy pDirectCtx) {
	ExecutablePass::postExecute(pDirectCtx);
}

PassType GraphicsPass::getPassType() const {
	return PassType::GraphicsPass;
}

}
