#include "Pass.h"
#include "PassVariant.h"

namespace Eureka {

Pass::Pass() {

}

auto Pass::getTag() const -> const std::string & {
	return _tag;
}

auto Pass::getPassVariant(const ShaderKeyword &keyword) -> std::shared_ptr<PassVariant> {
	auto iter = _passVariantMap.find(keyword.getBitset());
	if (iter != _passVariantMap.end()) {
		return iter->second;
	}

	auto pPassVariant = std::make_shared<PassVariant>(this);
	_passVariantMap[keyword.getBitset()] = pPassVariant;
	return pPassVariant;
}

auto Pass::getKeywordSet() const -> std::shared_ptr<ShaderKeywordSet> {
	return _pKeywordSet;
}

auto Pass::getStencilRef() const -> int {
	return _stencilRef;
}

auto Pass::getRenderQueue() const -> RenderQueueLabel {
	return _renderQueue;
}

}
