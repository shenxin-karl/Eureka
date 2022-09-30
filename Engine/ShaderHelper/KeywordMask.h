#pragma once
#include <bitset>
#include <memory>
#include <unordered_map>

namespace Eureka {

class SubPassVariant;
class KeywordMask {
public:
	constexpr static size_t kMaxKeyWord = 128;
	using FeatureKeywords = std::vector<std::string>;
public:
	KeywordMask() = default;
	void setFeatureKeywords(std::vector<FeatureKeywords> &&featureKeywords);
	void setShaderContent(const char *pShaderContent);
	void setKeyWord(const std::string &keyword, bool enable);
	auto findKeywordIndex(const std::string &keyword) const->size_t;
	auto getEnableKeywords() const -> std::vector<std::string>;
	auto getBitMask() const -> const std::bitset<kMaxKeyWord> &;
private:
	std::bitset<kMaxKeyWord>	 _keywordMask;
	std::vector<FeatureKeywords> _featureKeywords;
};

}
