#pragma once
#include <string>
#include <vector>
#include <d3d12.h>
#include <memory>
#include <unordered_map>
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Tool/D3Dx12.h>
#include "ShaderHelper/KeywordMask.h"
#include <filesystem>

namespace stdfs = std::filesystem;

namespace Eureka {

enum class ShaderType {
	VS = 0,
	HS = 1,
	DS = 2,
	GS = 3,
	PS = 4,
};

struct ShaderEntryPoint {
	ShaderType shaderType;
	std::string entryPoint;
};

class GraphicsPipeline {
public:
	GraphicsPipeline(std::weak_ptr<dx12lib::Device> pDevice, stdfs::path shaderPath);
	~GraphicsPipeline();
	void setDepthStencilFormat(DXGI_FORMAT depthStencilFormat);
	void setRenderTargetFormat(DXGI_FORMAT renderTargetFormat);
	void setRenderTargetFormats(std::vector<DXGI_FORMAT> renderTargetFormats);
	void addShaderFeatures(KeywordMask::FeatureKeywords featureKeywords);
	void setVertexShader(const std::string &entryPoint);
	void setHullShader(const std::string &entryPoint);
	void setDomainShader(const std::string &entryPoint);
	void setGeometryShader(const std::string &entryPoint);
	void setPixelShader(const std::string &entryPoint);
	void setBlendDesc(const D3D12_BLEND_DESC &blendDesc);
	void setRasterizerDesc(const D3D12_RASTERIZER_DESC &rasterizerDesc);
	void setDepthStencilDesc(const D3D12_DEPTH_STENCIL_DESC &depthStencilDesc);
	void setPrimitiveType(D3D12_PRIMITIVE_TOPOLOGY_TYPE type);
	auto getShaderContent() const -> std::string_view;
	auto getEntryPoints() const -> const std::vector<ShaderEntryPoint> &;
	auto getBlendDesc() const -> const D3D12_BLEND_DESC &;
	auto getRasterizerDesc() const -> const D3D12_RASTERIZER_DESC &;
	auto getDepthStencilDesc() const -> const D3D12_DEPTH_STENCIL_DESC &;
	auto getPrimitiveType() const -> D3D12_PRIMITIVE_TOPOLOGY_TYPE;
	auto getPSO() const -> std::shared_ptr<dx12lib::GraphicsPSO>;
	auto getPSO(const KeywordMask &keywordMask) const -> std::shared_ptr<dx12lib::GraphicsPSO>;
	auto getKeywordMask() const -> const KeywordMask &;
	bool hasShader(ShaderType shaderType) const;
private:
	stdfs::path _shaderFilePath;
	KeywordMask _keywordMask;
	std::string_view _shaderContent;
	DXGI_FORMAT _DSVFormat = DXGI_FORMAT_UNKNOWN;
	std::vector<DXGI_FORMAT> _RTVFormats;
	std::weak_ptr<dx12lib::Device> _pDevice;
	std::vector<ShaderEntryPoint> _entryPoints;
	D3D12_BLEND_DESC _blendDesc = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	D3D12_RASTERIZER_DESC _rasterizerDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	D3D12_DEPTH_STENCIL_DESC _depthStencilDesc = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	D3D12_PRIMITIVE_TOPOLOGY_TYPE _primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	mutable std::unordered_map<KeywordMask, std::shared_ptr<dx12lib::GraphicsPSO>, KeywordMask::Hasher> _psoMap;
};

}