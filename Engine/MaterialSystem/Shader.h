#pragma once
#include <memory>
#include <Dx12lib/dx12libStd.h>
#include "MaterialSystem/MaterialSystemStd.h"

namespace Eureka {

struct ShaderDesc;
class ShaderVariant;

class Shader {
	using ShaderVariantMap = std::unordered_map<KeywordBitMask, std::unique_ptr<ShaderVariant>>;
public:
	Shader(std::weak_ptr<dx12lib::Device> pDevice, std::string &&shaderMetaFile);
	~Shader();
	void setShaderName(std::string &&shaderName);
	auto getShaderContent() const -> std::string_view;
	auto getShaderVariant(const KeywordBitMask &bitMask) const -> const ShaderVariant *;
	auto getShaderDesc() const -> const ShaderDesc *;
	auto getDevice() const -> std::weak_ptr<dx12lib::Device>;
	auto getShaderName() const -> const std::string &;
private:
	std::string _shaderName;
	size_t _shaderContentLength;
	std::unique_ptr<char[]>	_pShaderContent;
	std::unique_ptr<ShaderDesc> _pShaderDesc;
	mutable ShaderVariantMap _shaderVariants;
	std::weak_ptr<dx12lib::Device> _pDevice;
};

}
