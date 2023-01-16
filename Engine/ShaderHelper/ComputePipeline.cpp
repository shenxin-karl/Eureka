#include <filesystem>
#include "ComputePipeline.h"
#include "ShaderContentLoader.h"
#include "ShaderHelper.h"
#include "ShaderInclude.h"
#include "ShaderLoader.h"
#include "Dx12lib/Device/Device.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "Foundation/Exception.h"

namespace Eureka {

ComputePipeline::ComputePipeline(std::weak_ptr<dx12lib::Device> pDevice, fs::path shaderPath)
: _shaderFilePath(std::move(shaderPath)), _pDevice(std::move(pDevice))
{
	_shaderContent = ShaderContentLoader::instance()->open(_shaderFilePath);
	if (_shaderContent.empty())
		Exception::Throw("Can't open the file {}", _shaderFilePath.string());
	_keywordMask.handleShaderContent(_shaderContent.data());
}

void ComputePipeline::setComputeShader(const std::string &entryPoints) {
	_entryPoint = entryPoints;
}

auto ComputePipeline::getPSO() const -> std::shared_ptr<dx12lib::ComputePSO> {
	return getPSO(_keywordMask);
}

auto ComputePipeline::getPSO(const KeywordMask &keywordMask) const -> std::shared_ptr<dx12lib::ComputePSO> {
	auto iter = _psoMap.find(keywordMask);
	if (iter != _psoMap.end())
		return iter->second;

	assert(!_entryPoint.empty());
	std::string key = _shaderFilePath.string();
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
	auto pShader = ShaderLoader::dxc(
		_shaderFilePath,
		_entryPoint,
		"cs_6_0",
		macros.data()
	);
	auto pSharedDevice = _pDevice.lock();
	auto pComputePSO = pSharedDevice->createComputePSO(key);
	pComputePSO->setComputeShader(pShader);
	ShaderHelper::generateRootSignature(pComputePSO);
	pComputePSO->finalize();

	_psoMap[keywordMask] = pComputePSO;
	return pComputePSO;
}

auto ComputePipeline::getKeywordMask() const -> const KeywordMask & {
	return _keywordMask;
}

}
