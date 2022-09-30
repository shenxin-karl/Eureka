#pragma once
#include <d3d12.h>
#include <string>
#include <vector>
#include <Dx12lib/Tool/D3Dx12.h>
#include <sol/types.hpp>

namespace Eureka {

struct ShaderEntryPoint {
	std::string_view version;
	std::string entryPoint;
};

struct SubPassDesc {
	SubPassDesc() = default;
	void addShaderFeature(const sol::as_table_t<std::vector<std::string>> &strings);
	void setVertexShader(const std::string &entryPoint);
	void setHullShader(const std::string &entryPoint);
	void setDomainShader(const std::string &entryPoint);
	void setGeometryShader(const std::string &entryPoint);
	void setPixelShader(const std::string &entryPoint);
	void setComputeShader(const std::string &entryPoint);
	void setAlphaToMask(bool enabled);
	void setBlend(const std::string &srcOp, const std::string &dstOp);
	void setBlendOp(const std::string &op);
	void setColorMask(const std::string &channel, int renderTarget = 0);
	void setConservative(const std::string &enabled);
	void setCull(const std::string &state);
	void setOffset(float offset);
	void setZClip(bool enabled);
	void setZTest(const std::string &op);
	void setZWrite(bool enabled);
	void finalized();
private:
	std::vector<ShaderEntryPoint> entryPoints;
	std::vector<std::vector<std::string>> shaderFeatures;
	D3D12_BLEND_DESC blendDesc = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	D3D12_RASTERIZER_DESC rasterizerDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
};

class ShaderMeta {
public:
	ShaderMeta(const std::string &luaScriptName);
	void setShaderFileName(const std::string &fileName);
private:
	std::string _fileName;
	std::vector<SubPassDesc> _subPassDescs;
};

}
