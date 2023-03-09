#pragma once
#include <filesystem>
#include <Dx12lib/Tool/DxcModule.h>
#include "Foundation/NonCopyable.h"

namespace Eureka {

namespace stdfs = std::filesystem;
namespace WRL = Microsoft::WRL;

class Pass;
class PropertyBlock;
class EffectCompiler;
class ShaderKeywordSet;

class Effect : NonCopyable {
	friend EffectCompiler;
public:
	Effect();
	~Effect();
	auto getEffectSourcePath() const -> const stdfs::path &;
	auto getPasses() const -> const std::vector<std::unique_ptr<Pass>> &;
	auto getPropertyBlock() const -> PropertyBlock *;
	auto getIncludeContent() const -> WRL::ComPtr<IDxcBlobEncoding>;
private:
	stdfs::path							_effectSourcePath;
	WRL::ComPtr<IDxcBlobEncoding>		_pIncludeContent;
	std::vector<std::unique_ptr<Pass>>	_passes;
	std::unique_ptr<PropertyBlock>		_propertyBlock;
};

}
