#include "MaterialKeyword.h"
#include "Material.h"
#include "EffectLab/Effect.h"
#include "EffectLab/Pass.h"
#include "EffectLab/ShaderKeyword.h"

namespace Eureka {

MaterialKeyword::MaterialKeyword(Material *pMaterial) : _pMaterial(pMaterial) {
	for (auto &pass : _pMaterial->_pEffect->getPasses()) {
		auto pShaderKeyword = std::make_unique<ShaderKeyword>(pass->getKeywordSet());
		_pPassVariants.push_back(pass->getPassVariant(*pShaderKeyword));
		_pPassKeywords.push_back(std::move(pShaderKeyword));
	}
}

MaterialKeyword::~MaterialKeyword() {
}

bool MaterialKeyword::isKeywordEnable(const std::string &keyword) const {
	for (auto &pShaderKeyword : _pPassKeywords) {
		if (pShaderKeyword->isEnabled(keyword)) {
			return true;
		}
	}
	return false;
}

bool MaterialKeyword::disableKeyword(const std::string &keyword, bool flush) {
	bool isModify = false;
	for (auto &pShaderKeyword : _pPassKeywords) {
		if (pShaderKeyword->disable(keyword)) {
			isModify = true;
		}
	}
	if (isModify && flush) {
		flushPassVariant();
	}
	return isModify;
}

bool MaterialKeyword::enableKeyword(const std::string &keyword, bool flush) {
	bool isModify = false;
	for (auto &pShaderKeyword : _pPassKeywords) {
		if (pShaderKeyword->enable(keyword)) {
			isModify = true;
		}
	}
	if (isModify && flush) {
		flushPassVariant();
	}
	return isModify;
}

auto MaterialKeyword::getPassVariant() const -> const std::vector<std::shared_ptr<PassVariant>> & {
	return _pPassVariants;
}

void MaterialKeyword::flushPassVariant() {
	auto &passes = _pMaterial->_pEffect->getPasses();
	for (size_t i = 0; i < passes.size(); ++i) {
		auto &pass = passes[i];
		_pPassVariants[i] = pass->getPassVariant(*_pPassKeywords[i]);
	}
}

}
