#include <cassert>
#include "SubPass.h"
#include "SubPassDesc.h"
#include "SubPassVariant.h"

namespace Eureka {

SubPass::SubPass(const Shader *pShader, std::shared_ptr<SubPassDesc> pSubPassDesc) 
: _pShader(pShader), _pSubPassDesc(std::move(pSubPassDesc)) {
	assert(_pSubPassDesc != nullptr);
}

auto SubPass::getSubPassName() const -> const std::string & {
	return _pSubPassDesc->getSubPassName();
}

auto SubPass::getSubPassDesc() const -> std::shared_ptr<SubPassDesc> {
	return _pSubPassDesc;
}

auto SubPass::getSubPassVariant(const KeywordBitMask &bitMask) -> std::shared_ptr<SubPassVariant> {
	auto iter = _subPassVariantMap.find(bitMask);
	if (iter != _subPassVariantMap.end())
		return iter->second;

	auto pSubPassVariant = std::make_shared<SubPassVariant>(this);
	_subPassVariantMap[bitMask] = pSubPassVariant;
	return pSubPassVariant;
}

auto SubPass::getShader() const -> const Shader * {
	return _pShader;
}

}
