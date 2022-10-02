#pragma once
#include <Dx12lib/Tool/D3Dx12.h>
#include <d3d12.h>
#include <string>
#include <vector>
#include <sol/types.hpp>

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

struct ShaderDesc {
	ShaderDesc() = default;
	ShaderDesc(const ShaderDesc &) = default;
	void setShaderFileName(const std::string &shaderFileName);
	void addShaderFeature(const sol::as_table_t<std::vector<std::string>> &strings);
	void setVertexShader(const std::string &entryPoint);
	void setHullShader(const std::string &entryPoint);
	void setDomainShader(const std::string &entryPoint);
	void setGeometryShader(const std::string &entryPoint);
	void setPixelShader(const std::string &entryPoint);
	void setAlphaToMask(bool enabled);
	void setBlendColor(const std::string &srcOp, const std::string &dstOp);
	void setBlendColor(const std::string &srcOp, const std::string &dstOp, size_t renderTarget);
	void setBlendAlpha(const std::string &srcOp, const std::string &dstOp);
	void setBlendAlpha(const std::string &srcOp, const std::string &dstOp, size_t renderTarget);
	void setBlendOp(const std::string &op);
	void setBlendOp(const std::string &op, size_t renderTarget);
	void setColorMask(const std::string &channel);
	void setColorMask(const std::string &channel, int renderTarget);
	void setConservative(bool enabled);
	void setCull(const std::string &state);
	void setOffset(float slopeScaledDepthBias, INT depthBias);
	void setZClip(bool enabled);
	void setZTest(const std::string &op);
	void setZWrite(bool enabled);
	void setPrimitiveType(const std::string &primitiveType);
	bool checkValid() const;
	auto getShaderFileName() const -> const std::string &;
	auto getEntryPoints() const -> const std::vector<ShaderEntryPoint> &;
	auto getShaderFeatures() const -> const std::vector<std::vector<std::string>> &;
	auto getBlendDesc() const -> const D3D12_BLEND_DESC &;
	auto getRasterizerDesc() const -> const D3D12_RASTERIZER_DESC &;
	auto getDepthStencilDesc() const -> const D3D12_DEPTH_STENCIL_DESC &;
	auto getPrimitiveType() const->D3D12_PRIMITIVE_TOPOLOGY_TYPE;
	bool hasShader(ShaderType shaderType) const;
private:
	std::string shaderFileName;
	std::vector<ShaderEntryPoint> entryPoints;
	std::vector<std::vector<std::string>> shaderFeatures;
	D3D12_BLEND_DESC blendDesc = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	D3D12_RASTERIZER_DESC rasterizerDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
};

}
