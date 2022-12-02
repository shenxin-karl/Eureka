#pragma once
#include <Dx12lib/dx12libStd.h>

namespace dx12lib {

struct IndirectParameter : D3D12_INDIRECT_ARGUMENT_DESC {
	IndirectParameter() noexcept : D3D12_INDIRECT_ARGUMENT_DESC() {
		Type = static_cast<D3D12_INDIRECT_ARGUMENT_TYPE>(0xFFFFFFFF);
	}
	void draw() noexcept {
		Type = D3D12_INDIRECT_ARGUMENT_TYPE_DRAW;
	}
	void drawIndexed() noexcept {
		Type = D3D12_INDIRECT_ARGUMENT_TYPE_DRAW_INDEXED;
	}
	void dispatch() noexcept {
		Type = D3D12_INDIRECT_ARGUMENT_TYPE_DISPATCH;
	}
	void vertexBufferView(size_t slot) noexcept {
		Type = D3D12_INDIRECT_ARGUMENT_TYPE_VERTEX_BUFFER_VIEW;
		VertexBuffer.Slot = static_cast<UINT>(slot);
	}
	void IndexBufferView() noexcept {
		Type = D3D12_INDIRECT_ARGUMENT_TYPE_INDEX_BUFFER_VIEW;
	}
	void constant(size_t rootParameterIndex, size_t destOffsetIn32BitValues, size_t num32BitValuesToSet) noexcept {
		Type = D3D12_INDIRECT_ARGUMENT_TYPE_CONSTANT;
		Constant.RootParameterIndex = static_cast<UINT>(rootParameterIndex);
		Constant.DestOffsetIn32BitValues = static_cast<UINT>(destOffsetIn32BitValues);
		Constant.Num32BitValuesToSet = static_cast<UINT>(num32BitValuesToSet);
	}
	void constantBufferView(size_t rootParameterIndex) noexcept {
		Type = D3D12_INDIRECT_ARGUMENT_TYPE_CONSTANT_BUFFER_VIEW;
		ConstantBufferView.RootParameterIndex = static_cast<UINT>(rootParameterIndex);
	}
	void shaderResourceView(size_t rootParameterIndex) noexcept {
		Type = D3D12_INDIRECT_ARGUMENT_TYPE_SHADER_RESOURCE_VIEW;
		ShaderResourceView.RootParameterIndex = static_cast<UINT>(rootParameterIndex);
	}
	void unorderedAccessView(size_t rootParameterIndex) noexcept {
		Type = D3D12_INDIRECT_ARGUMENT_TYPE_UNORDERED_ACCESS_VIEW;
		UnorderedAccessView.RootParameterIndex = static_cast<UINT>(rootParameterIndex);
	}
};


class CommandSignature {
	friend class CommandList;
public:
	CommandSignature(std::weak_ptr<Device> pDevice, size_t numParams);
	void destroy();
	void reset(size_t numParams);
	auto operator[](size_t index) -> IndirectParameter &;
	auto operator[](size_t index) const -> const IndirectParameter &;
	auto at(size_t index) -> IndirectParameter &;
	auto at(size_t index) const -> const IndirectParameter &;
	auto getByteStride() const -> size_t;
	void finalize(std::shared_ptr<RootSignature> pRootSignature = nullptr);
private:
	bool _finalized;
	size_t _byteStride;
	size_t _numParameters;
	std::weak_ptr<Device> _pDevice;
	WRL::ComPtr<ID3D12CommandSignature> _pCommandSignature;
	std::unique_ptr<IndirectParameter[]> _pParamArray;
};

}
