#pragma once
#include <dxgiformat.h>
#include <memory>
#include <vector>
#include <Dx12lib/dx12libStd.h>
#include "MaterialSystem/MaterialSystemStd.h"
#include <Dx12lib/Pipeline/ShaderRegister.hpp>
#include <RenderGraph/Job/Geometry.h>

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

class SubPass;
class SubPassVariant {
	using PSOMap = std::unordered_map<
		RenderTargetFormats, 
		std::shared_ptr<dx12lib::GraphicsPSO>,
		RenderTargetFormats::Hasher
	>;
public:
	SubPassVariant(const SubPass *pSubPass, const KeywordBitMask &bitMask);
	auto getPSO(const RenderTargetFormats &MRTFormats) const -> std::shared_ptr<dx12lib::GraphicsPSO>;
	auto getShaderLayoutMask() const -> rgph::ShaderLayoutMask;
	auto getBoundResources() const -> const std::vector<BoundResourceDesc> &;
private:
	void generateShaderReflectionInfo();
private:
	WRL::ComPtr<ID3DBlob>  _pVertexShader;
	WRL::ComPtr<ID3DBlob>  _pHullShader;
	WRL::ComPtr<ID3DBlob>  _pDomainShader;
	WRL::ComPtr<ID3DBlob>  _pGeometryShader;
	WRL::ComPtr<ID3DBlob>  _pPixelShader;
	const SubPass	      *_pSubPass;
	mutable PSOMap		   _psoMap;

	// generate by shader reflection 
	rgph::ShaderLayoutMask _shaderLayoutMask;
	std::vector<BoundResourceDesc> _boundResources;
	std::shared_ptr<dx12lib::RootSignature> _pRootSignature;
	std::unordered_map<std::string, CBufferVar> _cbufferVars;
};

}
