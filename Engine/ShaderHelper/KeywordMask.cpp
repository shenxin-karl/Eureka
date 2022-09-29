#include "KeywordMask.h"

namespace Eureka {

void KeywordMask::setFeatureKeywords(std::vector<FeatureKeywords> &&featureKeywords) {
	_featureKeywords = std::move(featureKeywords);
}

void KeywordMask::setShaderContent(const char *pShaderContent) {
	const char *pStart = pShaderContent;
	const char *pLast = nullptr;
	while (*pStart != '\0') {
		pLast = pStart + 1;
		while (*pLast != '\0' && *pLast != '\n')
			++pLast;


		pStart = pLast + 1;
	}
}

void KeywordMask::setKeyWord(const std::string &keyword, bool enable) {
	size_t index = findKeywordIndex(keyword);
	if (index == -1)
		return;

	if (_keywordMask.test(index) == enable)
		return;

	_keywordMask.set(index, enable);
	if (!enable)
		return;

	// ÊµÏÖ keyword µÄ»¥³â
	size_t tmp = index;
	size_t featureIndex;
	size_t baseIndex = 0;
	for (featureIndex = 0; featureIndex < _featureKeywords.size(); ++featureIndex) {
		if (_featureKeywords[featureIndex].size() > tmp) {
			baseIndex += _featureKeywords[featureIndex].size();
			break;
		}
		tmp -= _featureKeywords[featureIndex].size();
	}

	for (size_t i = 0; i < _featureKeywords[featureIndex].size(); ++i) {
		if (_featureKeywords[featureIndex][i] != keyword)
			_keywordMask.set(baseIndex + i, false);
	}
}

auto KeywordMask::findKeywordIndex(const std::string &keyword) const -> size_t {
	size_t index = 0;
	for (size_t i = 0; i < _featureKeywords.size(); ++i) {
		for (const auto &word : _featureKeywords[i]) {
			if (word == keyword)
				return index;
			++index;
		}
	}
	return -1;
}

auto KeywordMask::getEnableKeywords() const -> std::vector<std::string> {
	size_t index = 0;
	std::vector<std::string> keywords;
	for (size_t i = 0; i < _featureKeywords.size(); ++i) {
		for (const auto &word : _featureKeywords[i]) {
			if (_keywordMask.test(index))
				keywords.push_back(word);
			++index;
		}
	}
	return keywords;
}

auto KeywordMask::getBitMask() const -> const std::bitset<kMaxKeyWord> & {
	return _keywordMask;
}

}
