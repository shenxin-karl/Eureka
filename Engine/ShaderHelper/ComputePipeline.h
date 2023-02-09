#pragma once
#include <memory>
#include <string>
#include <Dx12lib/dx12libStd.h>
#include <filesystem>
#include "ShaderHelper/KeywordMask.h"

namespace fs = std::filesystem;

namespace Eureka {

class ComputePipeline {
	using ComputePSOMap = std::unordered_map<KeywordMask, std::shared_ptr<dx12lib::ComputePSO>, KeywordMask::Hasher>;
public:
	ComputePipeline(std::weak_ptr<dx12lib::Device> pDevice, fs::path shaderPath);
	void setComputeShader(const std::string &entryPoints);
	auto getPSO() const -> std::shared_ptr<dx12lib::ComputePSO>;
	auto getPSO(const KeywordMask &keywordMask) const -> std::shared_ptr<dx12lib::ComputePSO>;
	auto getKeywordMask() const -> const KeywordMask &;
private:
	fs::path _shaderFilePath;
	KeywordMask _keywordMask;
	std::string _entryPoint;
	mutable ComputePSOMap _psoMap;
	std::string_view _shaderContent;
	std::weak_ptr<dx12lib::Device> _pDevice;
};

}
