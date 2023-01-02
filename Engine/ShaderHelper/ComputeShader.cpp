#include "ComputeShader.h"
#include <filesystem>
#include <iostream>

#include "ShaderHelper.h"
#include "ShaderInclude.h"
#include "ShaderLoader.h"
#include "Dx12lib/Device/Device.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "Foundation/Exception.h"

namespace Eureka {


ComputeShader::ComputeShader(std::weak_ptr<dx12lib::Device> pDevice, const std::string &shaderFileName)
: _shaderFileName(shaderFileName), _pDevice(pDevice)
{
	_shaderContent = ShaderLoader::instance()->open(shaderFileName);
	if (_shaderContent.empty())
		Exception::Throw("Can't open the file {}", _shaderFileName);
	_keywordMask.handleShaderContent(_shaderContent.data());
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
	auto pBinaryBlob = ShaderHelper::DXCCompile(
		_shaderContent.data(),
		_shaderContent.length(),
		_shaderFileName,
		macros.data(),
		_entryPoint,
		"cs_6_0"
	);
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
