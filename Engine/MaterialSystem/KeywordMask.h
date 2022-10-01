#pragma once
#include <bitset>
#include <memory>
#include <unordered_map>
#include "MaterialSystem/MaterialSystemStd.h"

namespace Eureka {

class SubPassVariant;
class KeywordMask {
public:
	using FeatureKeywords = std::vector<std::string>;
public:
	KeywordMask() = default;
	void setFeatureKeywords(std::vector<FeatureKeywords> &&featureKeywords);
	void setShaderContent(const char *pShaderContent);
	void setKeyWord(const std::string &keyword, bool enable);
	auto findKeywordIndex(const std::string &keyword) const->size_t;
	auto getEnableKeywords() const -> std::vector<std::string>;
	auto getBitMask() const -> const std::bitset<kMaxKeyword> &;
private:
	std::bitset<kMaxKeyword>	 _keywordMask;
	std::vector<FeatureKeywords> _featureKeywords;
};

}
