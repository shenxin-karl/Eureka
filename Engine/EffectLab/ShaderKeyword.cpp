#include "ShaderKeyword.h"
#include "ShaderKeywordSet.h"
#include <fmt/format.h>

namespace Eureka {

ShaderKeyword::ShaderKeyword(std::shared_ptr<ShaderKeywordSet> pKeywordSet)
: _pKeywordSet(std::move(pKeywordSet)) {
}

bool ShaderKeyword::enable(const std::string &key) {
	return _pKeywordSet->enable(*this, key);
}

bool ShaderKeyword::disable(const std::string &key) {
	return _pKeywordSet->disable(*this, key);
}

bool ShaderKeyword::isEnabled(const std::string &key) const {
	return _pKeywordSet->isEnable(*this, key);
}

auto ShaderKeyword::getKeywordSet() const -> std::shared_ptr<ShaderKeywordSet> {
	return _pKeywordSet;
}

auto ShaderKeyword::getBitset() -> BitsetType & {
	return _bitset;
}

auto ShaderKeyword::getBitset() const -> const BitsetType & {
	return _bitset;
}

auto ShaderKeyword::toString() const -> std::string {
	size_t index = 0;
	std::string toReturn;
	for (const auto &features : _pKeywordSet->getFeatures()) {
		for (const auto &keyword : features) {
			if (_bitset.test(index)) {
				toReturn += fmt::format("_{}", keyword);
			}
			++index;
		}
	}
	return toReturn;
}

}
