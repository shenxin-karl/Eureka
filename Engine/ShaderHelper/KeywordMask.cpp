#include <cassert>
#include "KeywordMask.h"

namespace Eureka {

void KeywordMask::addShaderFeatures(FeatureKeywords features) {
	_featureKeywords.push_back(std::move(features));
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

auto KeywordMask::getBitMask() const -> const std::bitset<kMaxKeyword> &{
	return _keywordMask;
}

auto KeywordMask::getKeywordByIndex(size_t index) const -> const std::string * {
	assert(index < kMaxKeyword);
	size_t count = 0;
	for (size_t i = 0; i < _featureKeywords.size(); ++i) {
		count += _featureKeywords[i].size();
		if (count > index)
			return &_featureKeywords[i][count - index];
	}
	return nullptr;
}

bool operator==(const KeywordMask &lhs, const KeywordMask &rhs) {
	return lhs.getBitMask() == rhs.getBitMask()		     &&
		   lhs._featureKeywords == rhs._featureKeywords;
}

bool operator!=(const KeywordMask &lhs, const KeywordMask &rhs) {
	return !(lhs == rhs);
}

}