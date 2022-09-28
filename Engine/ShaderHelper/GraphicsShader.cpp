#include "GraphicsShader.h"

#include "GraphicsShaderVariant.h"

namespace Eureka {

GraphicsShader::GraphicsShader(const GraphicsShaderDesc &graphicsShaderDesc) {

}

void GraphicsShader::setKeyWord(const std::string &keyword, bool enable) {
	_keywordMask.setKeyWord(keyword, enable);
}

auto GraphicsShader::getShaderContent() const -> const std::string & {
	return _shaderContent;
}

auto GraphicsShader::getBlendDesc() const -> const D3D12_BLEND_DESC & {
	return _graphicsShaderDesc.blendDesc;
}

auto GraphicsShader::getRasterizerDesc() const -> const D3D12_RASTERIZER_DESC & {
	return _graphicsShaderDesc.rasterizerDesc;
}

auto GraphicsShader::getDepthStencilDesc() const -> const D3D12_DEPTH_STENCIL_DESC & {
	return _graphicsShaderDesc.depthStencilDesc;
}

auto GraphicsShader::getPrimitiveType() const -> D3D12_PRIMITIVE_TOPOLOGY_TYPE {
	return _graphicsShaderDesc.primitiveType;
}

auto GraphicsShader::getShaderVariant() const -> GraphicsShaderVariant * {
	auto iter = _shaderVariantMap.find(_keywordMask.getBitMask());
	if (iter != _shaderVariantMap.end())
		return iter->second.get();

	auto pShaderVariant = std::make_unique<GraphicsShaderVariant>(this);
	auto *pRet = pShaderVariant.get();
	_shaderVariantMap[_keywordMask.getBitMask()] = std::move(pShaderVariant);
	return pRet;
}

auto GraphicsShader::getEntryPoints() const -> const std::vector<ShaderEnterPoint> & {
	return _graphicsShaderDesc.enterPoints;
}

auto GraphicsShader::getDevice() const -> std::weak_ptr<dx12lib::Device> {
	return _graphicsShaderDesc.pDevice;
}

auto GraphicsShader::findKeywordIndex(const std::string &keyword) const -> size_t {
	return _keywordMask.findKeywordIndex(keyword);
}

auto GraphicsShader::getEnableKeywords() const -> std::vector<std::string> {
	return _keywordMask.getEnableKeywords();
}

}
