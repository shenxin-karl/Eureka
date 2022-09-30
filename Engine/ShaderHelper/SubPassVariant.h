#pragma once
#include <dxgiformat.h>
#include <memory>
#include <vector>
#include <Dx12lib/dx12libStd.h>
#include <RenderGraph/Job/Geometry.h>

namespace Eureka {

class SubPassVariant {
public:
	struct PSOItem {
		std::vector<DXGI_FORMAT> rtFormats;
		DXGI_FORMAT dsFormat = DXGI_FORMAT_UNKNOWN;
		std::shared_ptr<dx12lib::GraphicsPSO> pso;
	};
public:
	SubPassVariant(const SubPassVariant *pGraphicsShader);
	auto getPSO(std::vector<DXGI_FORMAT> rtFormats, DXGI_FORMAT dsFormat) const -> std::weak_ptr<dx12lib::GraphicsPSO>;
	auto getPSO(DXGI_FORMAT rtFormat, DXGI_FORMAT dsFormat) const -> std::weak_ptr<dx12lib::GraphicsPSO>;
	auto getPSO(DXGI_FORMAT dsFormat) const -> std::weak_ptr<dx12lib::GraphicsPSO>;
	auto getVertexInputSlots() -> const rgph::VertexInputSlots &;
	auto getNumRenderTarget() const -> size_t;
private:
	size_t _numRenderTarget = 0;
	const SubPassVariant *_pGraphicsShader;
	WRL::ComPtr<ID3DBlob> _pVertexShader;
	WRL::ComPtr<ID3DBlob> _pHullShader;
	WRL::ComPtr<ID3DBlob> _pGeometryShader;
	WRL::ComPtr<ID3DBlob> _pPixelShader;
	mutable std::vector<PSOItem> _psoItems;
	rgph::VertexInputSlots _vertexInputSlots;
};

}
