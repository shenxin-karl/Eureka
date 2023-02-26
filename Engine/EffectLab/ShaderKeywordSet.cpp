#include "ShaderKeywordSet.h"
#include "ShaderKeyword.h"
#include "Foundation/Exception.h"
#include <unordered_set>

namespace Eureka {

bool ShaderKeywordSet::enable(ShaderKeyword &keyword, const std::string &key) const {
	auto pFindResult = find(key);
	if (!pFindResult) {
		return false;
	}

	ShaderKeyword::BitsetType &bitset = keyword.getBitset();
	if (bitset.test(pFindResult->bitIndex)) {
		return false;
	}

	const auto &shaderFeature = _features[pFindResult->featureIndex];
	size_t startBitIndex = pFindResult->bitIndex - pFindResult->keywordIndex;
	for (size_t i = 0; i < shaderFeature.size(); ++i) {
		bool enable = (i == pFindResult->keywordIndex);
		bitset.set(startBitIndex + i, enable);
	}
	return true;
}

bool ShaderKeywordSet::disable(ShaderKeyword &keyword, const std::string &key) const {
	auto pFindResult = find(key);
	if (!pFindResult) {
		return false;
	}

	ShaderKeyword::BitsetType &bitset = keyword.getBitset();
	if (!bitset.test(pFindResult->bitIndex)) {
		return false;
	}

	bitset.set(pFindResult->bitIndex, false);
	return true;
}

bool ShaderKeywordSet::isEnable(const ShaderKeyword &keyword, const std::string &key) const {
	auto pFindResult = find(key);
	if (!pFindResult) {
		return false;
	}
	return keyword.getBitset().test(pFindResult->bitIndex);
}

auto ShaderKeywordSet::find(const std::string &key) const -> std::optional<FindResult> {
	size_t bitIndex = 0;
	for (size_t featureIndex = 0; featureIndex < _features.size(); ++featureIndex) {
		for (size_t keywordIndex = 0; keywordIndex < _features[featureIndex].size(); ++keywordIndex) {
			if (key == _features[featureIndex][keywordIndex]) {
				return FindResult {
					.featureIndex = featureIndex,
					.keywordIndex = keywordIndex,
					.bitIndex = bitIndex,
				};
			}
			++bitIndex;
		}
	}
	return std::nullopt;
}

void ShaderKeywordSet::addShaderFeatures(ShaderFeature features) {
	std::unordered_set<std::string> hashSet(features.begin(), features.end());
	for (const auto &shaderFeatures : _features) {
		for (const auto &key : shaderFeatures) {
			if (hashSet.contains(key)) {
				Exception::Throw("ShaderKeywordSet::addShaderFeatures redefinition key {} !", key);
			}
		}
	}
	_features.push_back(std::move(features));
}

}
