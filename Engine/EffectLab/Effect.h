#pragma once
#include <filesystem>
#include "Foundation/NonCopyable.h"

namespace Eureka {

namespace fs = std::filesystem;

class Pass;
class PropertyBlock;
class EffectCompiler;

class Effect : NonCopyable {
	friend EffectCompiler;
public:
	Effect();
	~Effect();
	auto getSourcePath() const -> const fs::path &;
	auto getPasses() const -> const std::vector<std::unique_ptr<Pass>> &;
	auto getPropertyBlock() const -> PropertyBlock *;
private:
	fs::path _sourcePath;
	std::vector<std::unique_ptr<Pass>> _passes;
	std::unique_ptr<PropertyBlock> _propertyBlock;
};

}
