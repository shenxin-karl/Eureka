#pragma once
#include <vector>
#include <string>
#include <bitset>
#include <optional>

namespace Eureka {

constexpr size_t kMaxKeyword = 128;
class KeywordMask {
public:
	using FeatureKeywords = std::vector<std::string>;
	struct Hasher {
		using result_type = std::size_t;
		result_type operator()(const Eureka::KeywordMask &keywordMask) const noexcept {
			std::hash<std::bitset<Eureka::kMaxKeyword>> hasher;
			return hasher(keywordMask.getBitMask());
		}
	};
public:
	KeywordMask() = default;
	void addShaderFeatures(FeatureKeywords &&features);
	void setKeyWord(const std::string &keyword, bool enable);
	auto findKeywordIndex(const std::string &keyword) const->size_t;
	auto getEnableKeywords() const->std::vector<std::string>;
	auto getBitMask() const -> const std::bitset<kMaxKeyword> &;
	auto getKeywordByIndex(size_t index) const -> const std::string *;
	friend bool operator==(const KeywordMask &lhs, const KeywordMask &rhs);
	friend bool operator!=(const KeywordMask &lhs, const KeywordMask &rhs);
private:
	std::bitset<kMaxKeyword>	 _keywordMask;
	std::vector<FeatureKeywords> _featureKeywords;
};


}
