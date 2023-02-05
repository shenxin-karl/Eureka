#pragma once
#include <optional>
#include <vector>
#include <string>

namespace Eureka {

class ShaderKeyword;
class ShaderKeywordSet {
public:
	using ShaderFeature = std::vector<std::string>;
	struct FindResult {
		size_t featureIndex;
		size_t keywordIndex;
		size_t bitIndex;
	};
public:
	bool enable(ShaderKeyword &keyword, const std::string &key) const;
	bool disable(ShaderKeyword &keyword, const std::string &key) const;
	bool isEnable(const ShaderKeyword &keyword, const std::string &key) const;
	void addShaderFeatures(ShaderFeature features);
	auto find(const std::string &key) const -> std::optional<FindResult>;
private:
	std::vector<ShaderFeature> _features;
};

}
