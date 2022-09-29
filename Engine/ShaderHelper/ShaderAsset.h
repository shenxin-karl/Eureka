#pragma once
#include <d3d12.h>
#include <string>
#include <vector>
#include <Dx12lib/Tool/D3Dx12.h>

struct SubPassDesc {
	void addVertexShader(const std::string &entryPoint);
	void addHullShader(const std::string &entryPoint);
	void addDomainShader(const std::string &entryPoint);
	void addGeometryShader(const std::string &entryPoint);
	void addPixelShader(const std::string &entryPoint);
	void addComputeShader(const std::string &entryPoint);
	void setAlphaToMask(const std::string &state);
	void setBlend(const std::string &srcOp, const std::string &dstOp);
	void setBlendOp();
	void finalized();
private:
	std::vector<std::string> entryPoints;
	D3D12_BLEND_DESC blendDesc = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	D3D12_RASTERIZER_DESC rasterizerDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
};

class ShaderMeta {
public:
	void setFileName(const std::string &fileName);
private:
	std::string _fileName;
	std::vector<SubPassDesc> _subPassDescs;
};
