#include "MaterialKeyword.h"
#include "Material.h"
#include "EffectLab/Effect.h"
#include "EffectLab/Pass.h"
#include "EffectLab/ShaderKeyword.h"

namespace Eureka {

MaterialKeyword::MaterialKeyword(Material *pMaterial) : _pMaterial(pMaterial) {
	size_t index = 0;
	for (auto &pass : _pMaterial->_pEffect->getPasses()) {
		if (pMaterial->_passMask.test(index)) {
			auto pShaderKeyword = std::make_unique<ShaderKeyword>(pass->getKeywordSet());
			_passVariants.push_back(pass->getPassVariant(*pShaderKeyword));
			_passKeywords.push_back(std::move(pShaderKeyword));
		} else {
			_passVariants.emplace_back(nullptr);
			_passKeywords.emplace_back(nullptr);
		}
		++index;
	}
}

MaterialKeyword::~MaterialKeyword() {
}

bool MaterialKeyword::isKeywordEnable(const std::string &keyword) const {
	for (auto &pShaderKeyword : _passKeywords) {
		if (pShaderKeyword->isEnabled(keyword)) {
			return true;
		}
	}
	return false;
}

bool MaterialKeyword::disableKeyword(const std::string &keyword, bool flush) {
	bool isModify = false;
	for (auto &pShaderKeyword : _passKeywords) {
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
	for (auto &pShaderKeyword : _passKeywords) {
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
	return _passVariants;
}

void MaterialKeyword::flushPassVariant() {
	auto &passes = _pMaterial->_pEffect->getPasses();
	for (size_t i = 0; i < passes.size(); ++i) {
		auto &pass = passes[i];
		if (_pMaterial->_passMask.test(i)) {
			_passVariants[i] = pass->getPassVariant(*_passKeywords[i]);
		} else {
			_passVariants[i] = nullptr;
		}
	}
}

}
