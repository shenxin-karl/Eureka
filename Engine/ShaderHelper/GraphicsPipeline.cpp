#include <cassert>
#include <Dx12lib/Device/Device.h>
#include <filesystem>
#include <fmt/format.h>
#include <Dx12lib/Pipeline/PipelineStateObject.h>
#include "GraphicsPipeline.h"
#include "ShaderContentLoader.h"
#include "ShaderHelper.h"
#include "ShaderInclude.h"
#include "ShaderLoader.h"
#include "Dx12lib/Pipeline/DXCShader.h"
#include "Foundation/Exception.h"

namespace Eureka {

GraphicsPipeline::GraphicsPipeline(std::weak_ptr<dx12lib::Device> pDevice, fs::path shaderPath)
: _shaderFilePath(std::move(shaderPath)), _pDevice(std::move(pDevice))
{
	_shaderContent = ShaderContentLoader::instance()->open(_shaderFilePath);
	if (_shaderContent.empty())
		Exception::Throw("Can't open the file {}", _shaderFilePath.string());
	_keywordMask.handleShaderContent(_shaderContent.data());
}

GraphicsPipeline::~GraphicsPipeline() {
}

void GraphicsPipeline::setDepthStencilFormat(DXGI_FORMAT depthStencilFormat) {
	_DSVFormat = depthStencilFormat;
}

void GraphicsPipeline::setRenderTargetFormat(DXGI_FORMAT renderTargetFormat) {
	_RTVFormats.clear();
	_RTVFormats.push_back(renderTargetFormat);
}

void GraphicsPipeline::setRenderTargetFormats(std::vector<DXGI_FORMAT> renderTargetFormats) {
	_RTVFormats = std::move(renderTargetFormats);
}

void GraphicsPipeline::addShaderFeatures(KeywordMask::FeatureKeywords featureKeywords) {
	_keywordMask.addShaderFeatures(std::move(featureKeywords));
}

void GraphicsPipeline::setVertexShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::VS));
	_entryPoints.push_back({ ShaderType::VS, entryPoint });
}

void GraphicsPipeline::setHullShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::VS));
	_entryPoints.push_back({ ShaderType::VS, entryPoint });
}

void GraphicsPipeline::setDomainShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::DS));
	_entryPoints.push_back({ ShaderType::DS, entryPoint });
}

void GraphicsPipeline::setGeometryShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::GS));
	_entryPoints.push_back({ ShaderType::GS, entryPoint });
}

void GraphicsPipeline::setPixelShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::PS));
	_entryPoints.push_back({ ShaderType::PS, entryPoint });
}

void GraphicsPipeline::setBlendDesc(const D3D12_BLEND_DESC &blendDesc) {
	_blendDesc = blendDesc;
}

void GraphicsPipeline::setRasterizerDesc(const D3D12_RASTERIZER_DESC &rasterizerDesc) {
	_rasterizerDesc = rasterizerDesc;
}

void GraphicsPipeline::setDepthStencilDesc(const D3D12_DEPTH_STENCIL_DESC &depthStencilDesc) {
	_depthStencilDesc = depthStencilDesc;
}

void GraphicsPipeline::setPrimitiveType(D3D12_PRIMITIVE_TOPOLOGY_TYPE type) {
	_primitiveType = type;
}

auto GraphicsPipeline::getShaderContent() const -> std::string_view {
	return _shaderContent;
}

auto GraphicsPipeline::getEntryPoints() const -> const std::vector<ShaderEntryPoint> &{
	return _entryPoints;
}

auto GraphicsPipeline::getBlendDesc() const -> const D3D12_BLEND_DESC &{
	return _blendDesc;
}

auto GraphicsPipeline::getRasterizerDesc() const -> const D3D12_RASTERIZER_DESC &{
	return _rasterizerDesc;
}

auto GraphicsPipeline::getDepthStencilDesc() const -> const D3D12_DEPTH_STENCIL_DESC &{
	return _depthStencilDesc;
}

auto GraphicsPipeline::getPrimitiveType() const -> D3D12_PRIMITIVE_TOPOLOGY_TYPE {
	return _primitiveType;
}

auto GraphicsPipeline::getPSO() const -> std::shared_ptr<dx12lib::GraphicsPSO> {
	return getPSO(_keywordMask);
}

auto GraphicsPipeline::getPSO(const KeywordMask &keywordMask) const -> std::shared_ptr<dx12lib::GraphicsPSO> {
	auto iter = _psoMap.find(keywordMask);
	if (iter != _psoMap.end())
		return iter->second;

	std::string key = _shaderFilePath.string();
	std::vector<D3D_SHADER_MACRO> macros;
	for (size_t i = 0; i < kMaxKeyword; ++i) {
		if (keywordMask.getBitMask().test(i)) {
			auto pKeyword = keywordMask.getKeywordByIndex(i);
			key += fmt::format("#{}", *pKeyword);
			macros.push_back(D3D_SHADER_MACRO{
				.Name = pKeyword->c_str(),
				.Definition = nullptr
			});
		}
	}
	macros.push_back(D3D_SHADER_MACRO{ nullptr, nullptr });

	using FuncType = void (dx12lib::GraphicsPSO:: *)(std::shared_ptr<dx12lib::IShader>);
	constexpr FuncType setterList[] = {
		&dx12lib::GraphicsPSO::setVertexShader,
		&dx12lib::GraphicsPSO::setHullShader,
		&dx12lib::GraphicsPSO::setDomainShader,
		&dx12lib::GraphicsPSO::setGeometryShader,
		&dx12lib::GraphicsPSO::setPixelShader,
	};

	std::string versionList[] = { "vs_6_0", "hs_6_0", "ds_6_0", "gs_6_0", "ps_6_0" };

	auto pSharedDevice = _pDevice.lock();
	auto pGraphicsPSO = pSharedDevice->createGraphicsPSO(key);
	auto pGraphicsPSOPtr = pGraphicsPSO.get();

	for (auto &entry : _entryPoints) {
		size_t index = static_cast<size_t>(entry.shaderType);
		auto pBinaryBlob = ShaderLoader::dxc(
			_shaderFilePath,
			entry.entryPoint,
			versionList[index],
			macros.data()
		);
		(pGraphicsPSOPtr->*setterList[index])(pBinaryBlob);
	}

	pGraphicsPSO->setRenderTargetFormats(_RTVFormats, _DSVFormat);
	pGraphicsPSO->setDepthStencilState(_depthStencilDesc);
	pGraphicsPSO->setBlendState(_blendDesc);
	pGraphicsPSO->setRasterizerState(_rasterizerDesc);
	pGraphicsPSO->setPrimitiveTopologyType(_primitiveType);
	ShaderHelper::generateRootSignature(pGraphicsPSO);
	ShaderHelper::generateVertexInput(pGraphicsPSO);
	pGraphicsPSO->finalize();
	_psoMap[keywordMask] = pGraphicsPSO;
	return pGraphicsPSO;
}

auto GraphicsPipeline::getKeywordMask() const -> const KeywordMask &{
	return _keywordMask;
}

bool GraphicsPipeline::hasShader(ShaderType shaderType) const {
	for (auto &entry : _entryPoints) {
		if (entry.shaderType == shaderType)
			return true;
	}
	return false;
}

}
