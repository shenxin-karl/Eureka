#pragma once
#include <memory>
#include <string>
#include <Dx12lib/dx12libStd.h>
#include "ShaderHelper/KeywordMask.h"

namespace Eureka {

class ComputeShader {
public:
	ComputeShader(std::weak_ptr<dx12lib::Device> pDevice, const std::string &shaderFileName);
	auto getPSO() const -> std::shared_ptr<dx12lib::ComputePSO>;
	auto getPSO(const KeywordMask &keywordMask) const -> std::shared_ptr<dx12lib::ComputePSO>;
	auto getKeywordMask() const -> const KeywordMask &;
private:
	KeywordMask _keywordMask;
	std::string _shaderFileName;
	std::string _entryPoint;
	size_t		_shaderContentLength;
	std::unique_ptr<char[]> _pShaderContent;
	std::weak_ptr<dx12lib::Device> _pDevice;
	mutable std::unordered_map<KeywordMask, std::shared_ptr<dx12lib::ComputePSO>, KeywordMask::Hasher> _psoMap;
};

}
