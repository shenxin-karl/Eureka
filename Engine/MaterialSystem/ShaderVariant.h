#pragma once
#include <RenderGraph/Job/ShaderLayout.h>
#include "MaterialSystem/MaterialSystemStd.h"
#include <vector>

namespace Eureka {
	
struct RenderTargetFormats {
	DXGI_FORMAT depthStencilFormat;
	DXGI_FORMAT renderTargetFormats[dx12lib::kMaxRenderTargetCount];
public:
	struct Hasher {
		size_t operator()(const RenderTargetFormats &MRTFormats) const noexcept {
			std::hash<std::string_view> hasher;
			return hasher(std::string_view((const char *)&MRTFormats, sizeof(RenderTargetFormats)));
		}
	};
public:
	RenderTargetFormats() {
		std::memset(this, 0, sizeof(*this));
	}
};

class ShaderVariant {
public:
	ShaderVariant(const Shader *pShader, const KeywordBitMask &bitMask);
	auto getPSO(const RenderTargetFormats &mrtFormats) const -> std::shared_ptr<dx12lib::GraphicsPSO>;
private:
	using PSOMap = std::unordered_map<RenderTargetFormats, 
		std::shared_ptr<dx12lib::GraphicsPSO>, 
		RenderTargetFormats::Hasher
	>;
	struct ShaderInput {
		std::string name;
		UINT bindCount;
		dx12lib::ShaderRegister shaderRegister;
	};
	void generateShaderReflectionInfo(std::shared_ptr<dx12lib::Device> pDevice);
private:
	const Shader  *_pShader;
	mutable PSOMap _psoMap;
	KeywordBitMask _keywordBitMask;

	WRL::ComPtr<ID3DBlob>  _pVertexShader;
	WRL::ComPtr<ID3DBlob>  _pHullShader;
	WRL::ComPtr<ID3DBlob>  _pDomainShader;
	WRL::ComPtr<ID3DBlob>  _pGeometryShader;
	WRL::ComPtr<ID3DBlob>  _pPixelShader;
	
	// generate by shader reflection 
	rgph::ShaderLayoutMask _shaderLayoutMask;
	std::vector<ShaderInput> _shaderInputViews;
	std::shared_ptr<dx12lib::RootSignature> _pRootSignature;
};

}