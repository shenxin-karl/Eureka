#include <filesystem>
#include <iostream>
#include "GraphicsShader.h"
#include "GraphicsShaderVariant.h"
#include "ShaderHelper/ShaderInclude.h"
#include "ShaderHelper/ShaderHelper.h"

namespace Eureka {

GraphicsShader::GraphicsShader(const GraphicsShaderDesc &graphicsShaderDesc) : _graphicsShaderDesc(std::move(graphicsShaderDesc)) {
	char error[256] = { '\0' };
	auto path = std::filesystem::path(_graphicsShaderDesc.fileName).parent_path().string();
	_pShaderContent = std::unique_ptr<char[]>(stb_include_file(
		const_cast<char*>(_graphicsShaderDesc.fileName.c_str()),
		nullptr, 
		const_cast<char*>(path.c_str()), 
		error
	));
	assert(_pShaderContent != nullptr);

	try {
		_keywordMask.setShaderContent(_pShaderContent.get());
	} catch (const std::string &errMsg) {
		std::string msg = std::format("In file {}: {}", _graphicsShaderDesc.fileName, errMsg);
		std::cerr << msg << std::endl;
		MessageBox(nullptr, msg.c_str(), "Error", MB_OK | MB_ICONHAND);
	} 
}

GraphicsShader::~GraphicsShader() {

}

auto GraphicsShader::getShaderContent() const -> const char *{
	return _pShaderContent.get();
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

auto GraphicsShader::getShaderVariant(const KeywordMask &keywordMask) const -> GraphicsShaderVariant * {
	auto iter = _shaderVariantMap.find(keywordMask.getBitMask());
	if (iter != _shaderVariantMap.end())
		return iter->second.get();

	auto pShaderVariant = std::make_unique<GraphicsShaderVariant>(this);
	auto *pRet = pShaderVariant.get();
	_shaderVariantMap[keywordMask.getBitMask()] = std::move(pShaderVariant);
	return pRet;
}

auto GraphicsShader::getEntryPoints() const -> const std::vector<ShaderEnterPoint> & {
	return _graphicsShaderDesc.enterPoints;
}

auto GraphicsShader::getDevice() const -> std::weak_ptr<dx12lib::Device> {
	return _graphicsShaderDesc.pDevice;
}

auto GraphicsShader::getShaderKeywordMask() const -> const KeywordMask & {
	return _keywordMask;
}

auto GraphicsShader::getGraphicsShaderDesc() const -> const GraphicsShaderDesc & {
	return _graphicsShaderDesc;
}

}
