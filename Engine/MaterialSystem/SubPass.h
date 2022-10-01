#pragma once
#include <memory>
#include <string>
#include <bitset>
#include <unordered_map>
#include "MaterialSystem/MaterialSystemStd.h"

namespace Eureka {

class SubPassVariant;
class Shader;
struct SubPassDesc;

class SubPass {
	using SubPassVariantMap = std::unordered_map<KeywordBitMask, std::shared_ptr<SubPassVariant>>;
public:
	explicit SubPass(const Shader *pShader, std::shared_ptr<SubPassDesc> pSubPassDesc);
	auto getSubPassName() const -> const std::string &;
	auto getSubPassDesc() const -> std::shared_ptr<SubPassDesc>;
	auto getSubPassVariant(const KeywordBitMask &bitMask) -> std::shared_ptr<SubPassVariant>;
	auto getShader() const -> const Shader *;
private:
	const Shader *_pShader;
	std::shared_ptr<SubPassDesc> _pSubPassDesc;
	mutable SubPassVariantMap _subPassVariantMap;
};

}
