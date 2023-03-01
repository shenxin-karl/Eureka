#pragma once
#include <filesystem>
#include "Foundation/NonCopyable.h"

namespace Eureka {

namespace fs = std::filesystem;

class Pass;
class PropertyBlock;
class EffectCompiler;
class ShaderKeywordSet;

class Effect : NonCopyable {
	friend EffectCompiler;
public:
	Effect();
	~Effect();
	auto getPasses() const -> const std::vector<std::unique_ptr<Pass>> &;
	auto getPropertyBlock() const -> PropertyBlock *;
private:
	std::string						    _passIncludeContent;
	std::vector<std::unique_ptr<Pass>>	_passes;
	std::unique_ptr<PropertyBlock>		_propertyBlock;
};

}
