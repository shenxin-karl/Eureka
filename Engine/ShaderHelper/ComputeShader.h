#pragma once
#include <memory>
#include <string>
#include <Dx12lib/dx12libStd.h>
#include "ShaderHelper/KeywordMask.h"

namespace Eureka {

class ComputeShader {
	using ComputePSOMap = std::unordered_map<KeywordMask, std::shared_ptr<dx12lib::ComputePSO>, KeywordMask::Hasher>;
public:
	ComputeShader(std::weak_ptr<dx12lib::Device> pDevice, const std::string &shaderFileName);
	void setComputeShader(const std::string &entryPoints);
	auto getPSO() const -> std::shared_ptr<dx12lib::ComputePSO>;
	auto getPSO(const KeywordMask &keywordMask) const -> std::shared_ptr<dx12lib::ComputePSO>;
	auto getKeywordMask() const -> const KeywordMask &;
private:
	size_t _shaderContentLength;
	KeywordMask _keywordMask;
	std::string _entryPoint;
	std::string _shaderFileName;
	mutable ComputePSOMap _psoMap;
	std::unique_ptr<char[]> _pShaderContent;
	std::weak_ptr<dx12lib::Device> _pDevice;
};

}
