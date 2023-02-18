#pragma once
#include <bitset>
#include <memory>

namespace Eureka {

class ShaderKeywordSet;
class ShaderKeyword {
public:
	constexpr static size_t kMaxShaderKeyword = 128;
	using BitsetType = std::bitset<kMaxShaderKeyword>;
	ShaderKeyword(const ShaderKeyword &) = delete;
	ShaderKeyword(std::shared_ptr<ShaderKeywordSet> pKeywordSet);
	bool enable(const std::string &key);
	bool disable(const std::string &key);
	bool isEnabled(const std::string &key) const;
	auto getKeywordSet() const -> std::shared_ptr<ShaderKeywordSet>;
	auto getBitset() -> BitsetType &;
	auto getBitset() const -> const BitsetType &;
private:
	BitsetType _bitset;
	std::shared_ptr<ShaderKeywordSet> _pKeywordSet;
};

}
