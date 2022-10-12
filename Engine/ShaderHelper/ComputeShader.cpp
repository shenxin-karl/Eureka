#include "ComputeShader.h"
#include <filesystem>
#include <iostream>
#include <sol/types.hpp>

#include "ShaderHelper.h"
#include "ShaderInclude.h"
#include "Dx12lib/Device/Device.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"

namespace Eureka {


ComputeShader::ComputeShader(std::weak_ptr<dx12lib::Device> pDevice, const std::string &shaderFileName)
: _shaderFileName(shaderFileName), _pDevice(pDevice)
{
	char error[256];
	std::filesystem::path path(shaderFileName);
	std::string dir = path.remove_filename().string();
	_pShaderContent = std::unique_ptr<char[]>(stb_include_file(
		const_cast<char *>(shaderFileName.c_str()),
		nullptr,
		dir.data(),
		error
	));

	if (_pShaderContent == nullptr) {
		std::cerr << error << std::endl;
		assert(false);
	}
	_shaderContentLength = std::strlen(_pShaderContent.get());
	_keywordMask.handleShaderContent(_pShaderContent.get());
}

void ComputeShader::setComputeShader(const std::string &entryPoints) {
	_entryPoint = entryPoints;
}

auto ComputeShader::getPSO() const -> std::shared_ptr<dx12lib::ComputePSO> {
	return getPSO(_keywordMask);
}

auto ComputeShader::getPSO(const KeywordMask &keywordMask) const -> std::shared_ptr<dx12lib::ComputePSO> {
	auto iter = _psoMap.find(keywordMask);
	if (iter != _psoMap.end())
		return iter->second;

	assert(!_entryPoint.empty());
	std::string key = _shaderFileName;
	std::vector<D3D_SHADER_MACRO> macros;
	for (size_t i = 0; i < kMaxKeyword; ++i) {
		if (keywordMask.getBitMask().test(i)) {
			auto pKeyword = keywordMask.getKeywordByIndex(i);
			key += std::format("#{}", *pKeyword);
			macros.push_back(D3D_SHADER_MACRO{
				.Name = pKeyword->c_str(),
				.Definition = nullptr
			});
		}
	}
	macros.push_back(D3D_SHADER_MACRO{ nullptr, nullptr });

#if defined(_DEBUG) || defined(DEBUG)
	auto pBinaryBlob = ShaderHelper::compile(
		dx12lib::to_wstring(_shaderFileName),
		macros.data(),
		_entryPoint,
		"cs_5_1"
	);
#else
	auto pBinaryBlob = ShaderHelper::compile(
		_pShaderContent.get(),
		_shaderContentLength,
		macros.data(),
		_entryPoint,
		"cs_5_1"
	);
#endif
	auto pSharedDevice = _pDevice.lock();
	auto pComputePSO = pSharedDevice->createComputePSO(key);
	pComputePSO->setComputeShader(pBinaryBlob);
	ShaderHelper::generateRootSignature(pComputePSO);
	pComputePSO->finalize();

	_psoMap[keywordMask] = pComputePSO;
	return pComputePSO;
}

auto ComputeShader::getKeywordMask() const -> const KeywordMask & {
	return _keywordMask;
}

}
