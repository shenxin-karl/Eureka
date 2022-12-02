#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Pipeline/ShaderRegister.hpp>
#include <optional>

namespace dx12lib {

class RootParameter : protected D3D12_ROOT_PARAMETER {
	constexpr static D3D12_ROOT_PARAMETER_TYPE kInvalidType = static_cast<D3D12_ROOT_PARAMETER_TYPE>(-1);
	friend class RootSignature;
public:
	RootParameter();
	RootParameter(const RootParameter &) = delete;
	RootParameter &operator=(const RootParameter &) = delete;
	~RootParameter();
	void clear();
	bool valid() const;
	void initAsConstants(ShaderRegister shaderRegister, size_t num32BitValues, D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL);
	void initAsDescriptorRange(ShaderRegister shaderRegister, UINT count, D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL);
	void initAsDescriptorTable(size_t rangeCount, D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL);
	void initAsDescriptorTable(const std::initializer_list<std::pair<ShaderRegister, size_t>> &initList, D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL);
	void setTableRange(size_t index, ShaderRegister shaderRegister, UINT count = 1);
	friend bool operator==(const RootParameter &lhs, const RootParameter &rhs);
};

struct ShaderParamLocation {
	ShaderParamLocation() = default;
	ShaderParamLocation(size_t rootParamIndex, size_t offsetOrNum32BitValues)
	: rootParamIndex(rootParamIndex), offset(offsetOrNum32BitValues) {}
public:
	size_t rootParamIndex;			// 根参数
	union {
		size_t offset;				// 在根参数的描述符表中的偏移
		size_t num32BitValues;		// 有多少个根常量	
	};
};

class RootSignature {
	static size_t getPerTableIndexByRangeType(D3D12_DESCRIPTOR_RANGE_TYPE type);
	using DescriptorsPerTable = std::array<uint8_t, kMaxDescriptorInRootParameter>;
	using ShaderParamLocationMap = std::unordered_map<ShaderRegister, ShaderParamLocation, ShaderRegisterHasher>;
protected:
	RootSignature(std::weak_ptr<Device> pDevice, size_t numRootParams, size_t numStaticSamplers = 0);
public:
	void reset(size_t numRootParams, size_t numStaticSamplers = 0);
	void finalize(D3D12_ROOT_SIGNATURE_FLAGS flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	void initStaticSampler(size_t index, const D3D12_STATIC_SAMPLER_DESC &desc);
	template<size_t N>
	void initStaticSampler(size_t index, const std::array<CD3DX12_STATIC_SAMPLER_DESC, N> &samplers);
	auto getRootSignature() const -> WRL::ComPtr<ID3D12RootSignature>;
	auto getDescriptorTableBitMask(D3D12_DESCRIPTOR_HEAP_TYPE heapType) -> std::bitset<kMaxRootParameter>;
	auto operator[](size_t index) -> RootParameter &;
	auto operator[](size_t index) const -> const RootParameter &;
	auto at(size_t index) -> RootParameter &;
	auto at(size_t index) const -> const RootParameter &;
	auto getShaderParamLocation(const ShaderRegister &sr) const -> std::optional<ShaderParamLocation>;
	auto getDescriptorPerTableByType(D3D12_DESCRIPTOR_HEAP_TYPE heapType) const -> const DescriptorsPerTable&;
	auto isFinalized() const -> bool;
private:
	bool _finalized = false;
	size_t _numRootParams;
	size_t _numStaticSamplers;
	std::weak_ptr<Device> _pDevice;
	
	ShaderParamLocationMap _shaderParamLocation;

	WRL::ComPtr<ID3D12RootSignature> _pRootSignature;
	std::unique_ptr<RootParameter[]> _pRootParamArray;
	std::unique_ptr<D3D12_STATIC_SAMPLER_DESC[]> _pStaticSamplerArray;

	DescriptorsPerTable				  _rootParamDescriptorPerTable[kDynamicDescriptorHeapCount];
	std::bitset<kMaxRootParameter> _rootParamBitMask[kDynamicDescriptorHeapCount];
};

template <size_t N>
void RootSignature::initStaticSampler(size_t index, const std::array<CD3DX12_STATIC_SAMPLER_DESC, N> &samplers) {
	size_t i = 0;
	size_t limit = std::min(index+N, _numStaticSamplers);
	for (size_t j = index; j < limit; ++i, ++j)
		_pStaticSamplerArray[i] = samplers[i];
}

}

