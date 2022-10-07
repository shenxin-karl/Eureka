#include <iostream>
#include <cassert>
#include <Dx12lib/Tool/D3Dx12.h>
#include <Dx12lib/Device/Device.h>
#include <filesystem>
#include <Dx12lib/Pipeline/PipelineStateObject.h>
#include "GraphicsShader.h"
#include "ShaderHelper.h"
#include "ShaderInclude.h"

namespace Eureka {

GraphicsShader::GraphicsShader(std::weak_ptr<dx12lib::Device> pDevice, const std::string &shaderFileName) 
: _shaderFileName(shaderFileName), _pDevice(std::move(pDevice)) 
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

GraphicsShader::~GraphicsShader() {
}

void GraphicsShader::setDepthStencilFormat(DXGI_FORMAT depthStencilFormat) {
	_DSVFormat = depthStencilFormat;
}

void GraphicsShader::setRenderTargetFormat(DXGI_FORMAT renderTargetFormat) {
	_RTVFormats.clear();
	_RTVFormats.push_back(renderTargetFormat);
}

void GraphicsShader::setRenderTargetFormats(std::vector<DXGI_FORMAT> renderTargetFormats) {
	_RTVFormats = std::move(renderTargetFormats);
}

void GraphicsShader::addShaderFeatures(KeywordMask::FeatureKeywords featureKeywords) {
	_keywordMask.addShaderFeatures(std::move(featureKeywords));
}

void GraphicsShader::setVertexShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::VS));
	_entryPoints.push_back({ ShaderType::VS, entryPoint });
}

void GraphicsShader::setHullShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::VS));
	_entryPoints.push_back({ ShaderType::VS, entryPoint });
}

void GraphicsShader::setDomainShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::DS));
	_entryPoints.push_back({ ShaderType::DS, entryPoint });
}

void GraphicsShader::setGeometryShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::GS));
	_entryPoints.push_back({ ShaderType::GS, entryPoint });
}

void GraphicsShader::setPixelShader(const std::string &entryPoint) {
	assert(!hasShader(ShaderType::PS));
	_entryPoints.push_back({ ShaderType::PS, entryPoint });
}

void GraphicsShader::setBlendDesc(const D3D12_BLEND_DESC &blendDesc) {
	_blendDesc = blendDesc;
}

void GraphicsShader::setRasterizerDesc(const D3D12_RASTERIZER_DESC &rasterizerDesc) {
	_rasterizerDesc = rasterizerDesc;
}

void GraphicsShader::setDepthStencilDesc(const D3D12_DEPTH_STENCIL_DESC &depthStencilDesc) {
	_depthStencilDesc = depthStencilDesc;
}

void GraphicsShader::setPrimitiveType(D3D12_PRIMITIVE_TOPOLOGY_TYPE type) {
	_primitiveType = type;
}

auto GraphicsShader::getShaderContent() const -> std::string_view {
	return std::string_view(_pShaderContent.get(), _shaderContentLength);
}

auto GraphicsShader::getEntryPoints() const -> const std::vector<ShaderEntryPoint> & {
	return _entryPoints;
}

auto GraphicsShader::getBlendDesc() const -> const D3D12_BLEND_DESC & {
	return _blendDesc;
}

auto GraphicsShader::getRasterizerDesc() const -> const D3D12_RASTERIZER_DESC & {
	return _rasterizerDesc;
}

auto GraphicsShader::getDepthStencilDesc() const -> const D3D12_DEPTH_STENCIL_DESC & {
	return _depthStencilDesc;
}

auto GraphicsShader::getPrimitiveType() const -> D3D12_PRIMITIVE_TOPOLOGY_TYPE {
	return _primitiveType;
}

auto GraphicsShader::getPSO() const -> std::shared_ptr<dx12lib::GraphicsPSO> {
	return getPSO(_keywordMask);
}

auto GraphicsShader::getPSO(const KeywordMask &keywordMask) const -> std::shared_ptr<dx12lib::GraphicsPSO> {
	auto iter = _psoMap.find(keywordMask);
	if (iter != _psoMap.end())
		return iter->second;

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
	
	using FuncType = void (dx12lib::GraphicsPSO:: *)(WRL::ComPtr<ID3DBlob>);
	constexpr FuncType setterList[] = {
		&dx12lib::GraphicsPSO::setVertexShader,
		&dx12lib::GraphicsPSO::setHullShader,
		&dx12lib::GraphicsPSO::setDomainShader,
		&dx12lib::GraphicsPSO::setGeometryShader,
		&dx12lib::GraphicsPSO::setPixelShader,
	};

	std::string versionList[] = { "vs_5_1", "hs_5_1", "ds_5_1", "gs_5_1", "ps_5_1" };

	auto pSharedDevice = _pDevice.lock();
	auto pGraphicsPSO = pSharedDevice->createGraphicsPSO(key);
	auto pGraphicsPSOPtr = pGraphicsPSO.get();
	for (auto &entry : _entryPoints) {
		size_t index = static_cast<size_t>(entry.shaderType);
		auto pBinaryBlob = ShaderHelper::compile(
			_pShaderContent.get(),
			_shaderContentLength,
			macros.data(),
			entry.entryPoint,
			versionList[index]
		);
		(pGraphicsPSOPtr->*setterList[index])(pBinaryBlob);
	}

	pGraphicsPSO->setRenderTargetFormats(_RTVFormats, _DSVFormat);
	pGraphicsPSO->setDepthStencilState(_depthStencilDesc);
	pGraphicsPSO->setBlendState(_blendDesc);
	pGraphicsPSO->setRasterizerState(_rasterizerDesc);
	pGraphicsPSO->setPrimitiveTopologyType(_primitiveType);
	ShaderHelper::generateGraphicsRootSignature(_pDevice.lock(), pGraphicsPSO);
	ShaderHelper::generateVertexInput(pGraphicsPSO);
	pGraphicsPSO->finalize();
	_psoMap[keywordMask] = pGraphicsPSO;
	return pGraphicsPSO;
}

auto GraphicsShader::getKeywordMask() const -> const KeywordMask & {
	return _keywordMask;
}

bool GraphicsShader::hasShader(ShaderType shaderType) const {
	for (auto &entry : _entryPoints) {
		if (entry.shaderType == shaderType)
			return true;
	}
	return false;
}

}