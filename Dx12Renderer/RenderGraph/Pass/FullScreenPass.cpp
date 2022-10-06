#include "FullScreenPass.h"
#include "FullScreenRenderable.h"

namespace rgph {

FullScreenPass::FullScreenPass(const std::string &passName, bool rtActive, bool dsActive)
: GraphicsPass(passName)
{
}

void FullScreenPass::execute(dx12lib::DirectContextProxy pDirectCtx) {
	GraphicsPass::execute(pDirectCtx);
	assert(_pFullScreenRenderable != nullptr);
	_pFullScreenRenderable->execute(*pDirectCtx);
}

void FullScreenPass::setFullScreenRenderable(std::shared_ptr<FullScreenRenderable> pFullScreenRenderable) {
	_pFullScreenRenderable = std::move(pFullScreenRenderable);
}

auto FullScreenPass::getFullScreenRenderable() const -> std::shared_ptr<FullScreenRenderable> {
	return _pFullScreenRenderable;
}

PassType FullScreenPass::getPassType() const {
	return PassType::FullScreenPass;
}

}
