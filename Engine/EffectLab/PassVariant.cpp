#include "PassVariant.h"
#include "Effect.h"
#include "PropertyBlock.h"
#include "ShaderKeywordSet.h"
#include "Application/Application.h"
#include "Dx12lib/Pipeline/ShaderInclude.h"
#include "Objects/PathManager.h"
#include "ShaderHelper/ShaderLoader.h"

namespace Eureka {

PassVariant::PassVariant(Pass *pass, const ShaderKeyword &keyword) {
	_tag = pass->getTag();
	_stencilRef = pass->getStencilRef();
	_renderQueue = pass->getRenderQueue();

	auto pDevice = Application::getDevice();
	_pso = pDevice->createGraphicsPSO(_tag + keyword.toString());
	_pso->setRasterizerState(pass->getRasterizerDesc());
	_pso->setBlendState(pass->getBlendDesc());
	_pso->setDepthStencilState(pass->getDepthStencilDesc());

	auto filePath = pass->getEffect()->getEffectSourcePath().string();
	auto pSourceCode = pass->getSourceCode();
	std::string_view source(static_cast<const char *>(pSourceCode->GetBufferPointer()), pSourceCode->GetBufferSize());
	ShaderLoader::DxcCompileDesc1 desc = {
		filePath,
		source,
		stdfs::last_write_time(filePath)
	};

	size_t index = 0;
	std::vector<D3D_SHADER_MACRO> macros;
	const auto &bitset = keyword.getBitset();
	auto pKeywordSet = keyword.getKeywordSet();
	for (const auto &features : pKeywordSet->getFeatures()) {
		for (const auto &key : features) {
			if (bitset.test(index)) {
				macros.push_back({
					key.c_str(),
					"1"
				});
			}
			++index;
		}
	}
	macros.push_back({ nullptr, nullptr });
	desc.defines = macros.data();

	const auto *pEffect = pass->getEffect();
	const auto *pPropertyBlock = pEffect->getPropertyBlock();
	dx12lib::ShaderInclude shaderInclude;
	shaderInclude.addSearchDirectory(PathManager::instance()->getAssetPath());
	shaderInclude.addVirtualFile("generated/include.hlsl", pEffect->getIncludeContent());
	shaderInclude.addVirtualFile("generated/properties.hlsl", pPropertyBlock->getGeneratedPropertiesContent());
	desc.pInclude = &shaderInclude;

	if (!pass->getHullEntryPoint().empty()) {
		desc.entryPoint = pass->getHullEntryPoint();
		desc.target = "hs_6_0";
		_pso->setHullShader(ShaderLoader::dxc(desc));
	}
	if (!pass->getDomainEntryPoint().empty()) {
		desc.entryPoint = pass->getDomainEntryPoint();
		desc.target = "ds_6_0";
		_pso->setDomainShader(ShaderLoader::dxc(desc));
	}
	if (!pass->getVertexEntryPoint().empty()) {
		desc.entryPoint = pass->getVertexEntryPoint();
		desc.target = "vs_6_0";
		_pso->setVertexShader(ShaderLoader::dxc(desc));
	}
	if (!pass->getGeometryEntryPoint().empty()) {
		desc.entryPoint = pass->getGeometryEntryPoint();
		desc.target = "gs_6_0";
		_pso->setGeometryShader(ShaderLoader::dxc(desc));
	}
	if (!pass->getPixelEntryPoint().empty()) {
		desc.entryPoint = pass->getPixelEntryPoint();
		desc.target = "ps_6_0";
		_pso->setPixelShader(ShaderLoader::dxc(desc));
	}
	_pso->finalize();
}

auto PassVariant::getStencilRef() const -> int {
	return _stencilRef;
}

auto PassVariant::getRenderQueue() const -> RenderQueueLabel {
	return _renderQueue;
}

auto PassVariant::getPipelineStateObject() const -> const std::shared_ptr<dx12lib::GraphicsPSO> & {
	return _pso;
}

}
