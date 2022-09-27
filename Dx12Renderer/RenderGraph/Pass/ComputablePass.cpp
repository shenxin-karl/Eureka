#include "ComputablePass.h"
#include "RenderGraph/Technique/Computable.h"

namespace rgph {

void ComputablePass::execute(dx12lib::DirectContextProxy pDirectCtx) {
	ExecutablePass::execute(pDirectCtx);
	assert(_pComputable != nullptr);
	_pComputable->compute(*pDirectCtx);
}

void ComputablePass::setComputable(std::shared_ptr<Computable> pComputable) {
	_pComputable = pComputable;
}

auto ComputablePass::getComputable() const -> std::shared_ptr<Computable> {
	return _pComputable;
}

PassType ComputablePass::getPassType() const {
	return PassType::ComputablePass;
}

}
