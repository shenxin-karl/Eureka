#pragma once
#include <memory>
#include <string>
#include <vector>

namespace Eureka {

class Material;
class ShaderKeyword;
class PassVariant;
class MaterialKeyword {
public:
	explicit MaterialKeyword(Material *pMaterial);
	bool isKeywordEnable(const std::string &keyword) const;
	bool disableKeyword(const std::string &keyword, bool flush);
	bool enableKeyword(const std::string &keyword, bool flush);
	auto getPassVariant() const -> const std::vector<std::shared_ptr<PassVariant>> &;
	void flushPassVariant();
private:
	Material *									_pMaterial;
	std::vector<std::unique_ptr<ShaderKeyword>> _pPassKeywords;
	std::vector<std::shared_ptr<PassVariant>>	_pPassVariants;	
};

}
