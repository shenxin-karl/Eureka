#include <cassert>
#include "KeywordMask.h"
#include <unordered_set>
#include <fmt/format.h>

namespace Eureka {

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
	for (featureIndex = 0; featureIndex < _pFeatureKeywords->size(); ++featureIndex) {
		if ((*_pFeatureKeywords)[featureIndex].size() > tmp)
			break;
		baseIndex += (*_pFeatureKeywords)[featureIndex].size();
		tmp -= (*_pFeatureKeywords)[featureIndex].size();
	}

	for (size_t i = 0; i < (*_pFeatureKeywords)[featureIndex].size(); ++i) {
		if ((*_pFeatureKeywords)[featureIndex][i] != keyword)
			_keywordMask.set(baseIndex + i, false);
	}
}

auto KeywordMask::findKeywordIndex(const std::string &keyword) const -> size_t {
	size_t index = 0;
	for (size_t i = 0; i < _pFeatureKeywords->size(); ++i) {
		for (const auto &word : (*_pFeatureKeywords)[i]) {
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
	for (size_t i = 0; i < _pFeatureKeywords->size(); ++i) {
		for (const auto &word : (*_pFeatureKeywords)[i]) {
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
	for (size_t i = 0; i < _pFeatureKeywords->size(); ++i) {
		if (index < (*_pFeatureKeywords)[i].size())
			return &(*_pFeatureKeywords)[i][index];
		index -= (*_pFeatureKeywords)[i].size();
	}
	return nullptr;
}

auto KeywordMask::hasKeyword(const std::string &keyword) const -> bool {
	auto index = findKeywordIndex(keyword);
	if (index == -1)
		return false;
	return _keywordMask.test(index);
}

bool operator==(const KeywordMask &lhs, const KeywordMask &rhs) {
	return lhs.getBitMask() == rhs.getBitMask()		     &&
		   lhs._pFeatureKeywords == rhs._pFeatureKeywords;
}

bool operator!=(const KeywordMask &lhs, const KeywordMask &rhs) {
	return !(lhs == rhs);
}

KeywordMask::KeywordMask() {
	_pFeatureKeywords = std::make_shared<std::vector<FeatureKeywords>>();
}

void KeywordMask::handleShaderContent(const char *pShaderContent) {
		std::string_view pragmaKeyword = "#pragma";
		std::string_view featureKeyword = "shader_feature";

		std::unordered_set<std::string> featureKeywords;
		auto handleFeature = [&](const char *pStart, const char *pLast) {
			size_t length = pLast - pStart;
			if (length < pragmaKeyword.length() || length < featureKeyword.length())
				return;
			if (std::strncmp(pStart, pragmaKeyword.data(), pragmaKeyword.length()) != 0)
				return;
			pStart += pragmaKeyword.length();
			while (*pStart == ' ' && pStart < pLast)
				++pStart;

			length = pLast - pStart;
			if (length < featureKeyword.length())
				return;

			pStart += featureKeyword.length();
			FeatureKeywords keywords;
			while (pStart < pLast) {
				while (pStart < pLast && (*pStart == ' ' || *pStart == '\r' || *pStart == '\t'))
					++pStart;

				auto pEnd = pStart+1;
				while (pEnd < pLast && *pEnd != ' ' && *pEnd != '\t' && *pEnd != '\r')
					++pEnd;

				if (!((pEnd - pStart) == 1 && *pStart == '_')) {
					std::string keyword(pStart, pEnd);
					auto iter = featureKeywords.find(keyword);
					if (iter != featureKeywords.end())
						throw fmt::format("Duplicate shader_feature keyword: {}", keyword);

					featureKeywords.insert(keyword);
					keywords.emplace_back(std::move(keyword));
				}
				pStart = pEnd+1;
			}
			_pFeatureKeywords->push_back(std::move(keywords));
		};

		const char *pStart = pShaderContent;
		const char *pLast = nullptr;
		while (*pStart != '\0') {
			pLast = pStart + 1;
			while (*pLast != '\0' && *pLast != '\n')
				++pLast;

			try {
				handleFeature(pStart, pLast);
			} catch (...) {
				_pFeatureKeywords->clear();
				throw;
			}
			pStart = pLast + 1;
		}
}

void KeywordMask::addShaderFeatures(FeatureKeywords features) {
	_pFeatureKeywords->push_back(std::move(features));
}

}
