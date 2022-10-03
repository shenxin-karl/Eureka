#include <Dx12lib/Device/Device.h>
#include <Dx12lib/Pipeline/RootSignature.h>
#include <optional>

namespace dx12lib {

RootParameter::RootParameter() {
	std::memset(this, 0, sizeof(*this));
	ParameterType = kInvalidType;
}

RootParameter::~RootParameter() {
	clear();
}

void RootParameter::clear() {
	if (ParameterType == D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE) {
		assert(DescriptorTable.pDescriptorRanges != nullptr);
		delete[] DescriptorTable.pDescriptorRanges;
		DescriptorTable.pDescriptorRanges = nullptr;
	}
	ParameterType = kInvalidType;
}

bool RootParameter::valid() const {
	return ParameterType != kInvalidType;
}

void RootParameter::initAsConstants(ShaderRegister shaderRegister, size_t num32BitValues, D3D12_SHADER_VISIBILITY visibility) {
	assert(shaderRegister.slot.isCBV());
	assert(!valid());
	ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	ShaderVisibility = visibility;
	Constants.Num32BitValues = static_cast<UINT>(num32BitValues);
	Constants.ShaderRegister = static_cast<UINT>(shaderRegister.slot.getRegisterId());
	Constants.RegisterSpace = static_cast<UINT>(shaderRegister.space);
}

void RootParameter::initAsDescriptorRange(ShaderRegister shaderRegister, UINT count, D3D12_SHADER_VISIBILITY visibility) {
	assert(!valid());
	clear();
	initAsDescriptorTable(1, visibility);
	setTableRange(0, shaderRegister, count);
}

void RootParameter::initAsDescriptorTable(size_t rangeCount, D3D12_SHADER_VISIBILITY visibility) {
	assert(!valid());
	assert(DescriptorTable.pDescriptorRanges == nullptr);
	ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	ShaderVisibility = visibility;
	DescriptorTable.NumDescriptorRanges = static_cast<UINT>(rangeCount);
	DescriptorTable.pDescriptorRanges = new D3D12_DESCRIPTOR_RANGE[rangeCount];
}

void RootParameter::initAsDescriptorTable(const std::initializer_list<std::pair<ShaderRegister, size_t>> &initList,
	D3D12_SHADER_VISIBILITY visibility)
{
	assert(!valid());
	assert(DescriptorTable.pDescriptorRanges == nullptr);
	assert(initList.size() > 0);
	ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	ShaderVisibility = visibility;
	DescriptorTable.NumDescriptorRanges = static_cast<UINT>(initList.size());
	DescriptorTable.pDescriptorRanges = new D3D12_DESCRIPTOR_RANGE[initList.size()];
	size_t i = 0; 
	for (auto &item : initList) {
		D3D12_DESCRIPTOR_RANGE &range = const_cast<D3D12_DESCRIPTOR_RANGE &>(DescriptorTable.pDescriptorRanges[i]);
		range.RangeType = item.first.slot.getDescriptorRangeType();
		range.NumDescriptors = static_cast<UINT>(item.second);
		range.BaseShaderRegister = static_cast<UINT>(item.first.slot.getRegisterId());
		range.RegisterSpace = static_cast<UINT>(item.first.space);
		range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		++i;
	}
}

void RootParameter::setTableRange(size_t index, ShaderRegister shaderRegister, UINT count) {
	assert(valid());
	assert(DescriptorTable.pDescriptorRanges != nullptr);
	assert(index < DescriptorTable.NumDescriptorRanges);
	D3D12_DESCRIPTOR_RANGE &range = const_cast<D3D12_DESCRIPTOR_RANGE &>(DescriptorTable.pDescriptorRanges[index]);
	range.RangeType = shaderRegister.slot.getDescriptorRangeType();
	range.NumDescriptors = count;
	range.BaseShaderRegister = static_cast<UINT>(shaderRegister.slot.getRegisterId());
	range.RegisterSpace = static_cast<UINT>(shaderRegister.space);
	range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
}

bool operator==(const RootParameter &lhs, const RootParameter &rhs) {
	return std::memcmp(&lhs, &rhs, sizeof(RootParameter));
}

////////////////////////////////////////RootSignature/////////////////////////////////////////////////

RootSignature::RootSignature(std::weak_ptr<Device> pDevice, size_t numRootParams, size_t numStaticSamplers) : _pDevice(pDevice) {
	reset(numRootParams, numStaticSamplers);
}

void RootSignature::reset(size_t numRootParams, size_t numStaticSamplers) {
	assert(numRootParams > 0);
	_finalized = false;
	_numRootParams = numRootParams;
	_numStaticSamplers = numStaticSamplers;
	_shaderParamLocation.clear();
	_pRootParamArray = std::make_unique<RootParameter[]>(numRootParams);
	_shaderParamLocation.clear();
	if (numStaticSamplers > 0)
		_pStaticSamplerArray = std::make_unique<D3D12_STATIC_SAMPLER_DESC[]>(numStaticSamplers);

	for (size_t i = 0; i < kDynamicDescriptorHeapCount; ++i) {
		std::fill(_rootParamDescriptorPerTable[i].begin(), _rootParamDescriptorPerTable[i].end(), 0);
		_rootParamBitMask[i] = 0;
	}
}

void RootSignature::finalize(D3D12_ROOT_SIGNATURE_FLAGS flags) {
	if (_finalized) {
		assert(false);
		return;
	}

	D3D12_ROOT_SIGNATURE_DESC rootDesc(
		static_cast<UINT>(_numRootParams),
		_pRootParamArray.get(), 
		static_cast<UINT>(_numStaticSamplers),
		_pStaticSamplerArray.get(),
		flags
	);

	// build root Signature 
	WRL::ComPtr<ID3DBlob> serializedRootSig = nullptr;
	WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(
		&rootDesc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&serializedRootSig,
		&errorBlob
	);

	if (FAILED(hr)) {
		OutputDebugString(static_cast<const char *>(errorBlob->GetBufferPointer()));
		ThrowIfFailed(hr);
	}

	ThrowIfFailed(_pDevice.lock()->getD3DDevice()->CreateRootSignature(
		0,
		serializedRootSig->GetBufferPointer(),
		serializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(&_pRootSignature)
	));

	// 统计好每个根参数有多少个描述符
	size_t numDescriptors = 0;
	for (size_t rootParamIndex = 0; rootParamIndex < _numRootParams; ++rootParamIndex) {
		const RootParameter &rootParam = _pRootParamArray[rootParamIndex];

		switch (rootParam.ParameterType) {
		case D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE: {
			auto &descriptorTable = rootParam.DescriptorTable;
			size_t rangeCount = descriptorTable.NumDescriptorRanges;
			size_t tableIndex = getPerTableIndexByRangeType(descriptorTable.pDescriptorRanges[0].RangeType);
			assert(rangeCount <= static_cast<uint8_t>(-1));

			size_t offset = 0;
			for (size_t i = 0; i < rangeCount; ++i) {
				const D3D12_DESCRIPTOR_RANGE &range = rootParam.DescriptorTable.pDescriptorRanges[i];
				if (range.NumDescriptors <= 0)
					continue;

				// 统计每个寄存器的使用
				for (size_t j = 0; j < range.NumDescriptors; ++j, ++offset) {
					size_t baseRegister = range.BaseShaderRegister + j;
					RegisterSlot slot(range.RangeType, baseRegister);
					RegisterSpace space = static_cast<RegisterSpace>(range.RegisterSpace);
					ShaderRegister shaderRegister(slot, space);
					ShaderParamLocation location(rootParamIndex, offset);
					_shaderParamLocation[shaderRegister] = location;
				}

				_rootParamDescriptorPerTable[tableIndex][rootParamIndex] += static_cast<uint8_t>(range.NumDescriptors);
				_rootParamBitMask[tableIndex].set(rootParamIndex);
			}
			numDescriptors += _rootParamDescriptorPerTable[tableIndex][rootParamIndex];
			break;
		}
		case D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS: {
			const auto &constants = rootParam.Constants;
			RegisterSlot slot(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, constants.ShaderRegister);
			RegisterSpace space = static_cast<RegisterSpace>(constants.RegisterSpace);
			ShaderRegister shaderRegister(slot, space);
			ShaderParamLocation location(rootParamIndex, constants.Num32BitValues);
			_shaderParamLocation[shaderRegister] = location;
			break;
		}
		default: {
			assert(false && "Currently, no single descriptor is supported");
			break;
		}
		}
	} 
	_finalized = true;
}

void RootSignature::initStaticSampler(size_t index, const D3D12_STATIC_SAMPLER_DESC &desc) {
	assert(index < _numStaticSamplers);
	_pStaticSamplerArray[index] = desc;
}


WRL::ComPtr<ID3D12RootSignature> RootSignature::getRootSignature() const {
	return _pRootSignature;
}

std::bitset<kMaxDescriptorTables> RootSignature::getDescriptorTableBitMask(D3D12_DESCRIPTOR_HEAP_TYPE heapType) {
	switch (heapType) {
	case D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV:
		return _rootParamBitMask[0];
	case D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER:
		return _rootParamBitMask[1];
	default:
		assert(false);
		return { 0 };
	}
}

RootParameter &RootSignature::operator[](size_t index) {
	assert(index < _numRootParams);
	return _pRootParamArray[index];
}

const RootParameter &RootSignature::operator[](size_t index) const {
	assert(index < _numRootParams);
	return _pRootParamArray[index];
}

RootParameter &RootSignature::at(size_t index) {
	return (*this)[index];
}

const RootParameter &RootSignature::at(size_t index) const {
	return (*this)[index];
}

std::optional<ShaderParamLocation> RootSignature::getShaderParamLocation(const ShaderRegister &sr) const {
	auto iter = _shaderParamLocation.find(sr);
	if (iter != _shaderParamLocation.end())
		return iter->second;
	return std::nullopt;
}

const RootSignature::DescriptorsPerTable &
RootSignature::getDescriptorPerTableByType(D3D12_DESCRIPTOR_HEAP_TYPE heapType) const {
	switch (heapType) {
	case D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV:
		return _rootParamDescriptorPerTable[0];
	case D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER:
		return _rootParamDescriptorPerTable[1];
	default:
		assert(false);
		throw std::runtime_error("invalid D3D12_DESCRIPTOR_HEAP_TYPE");
	}
}

bool RootSignature::isFinalized() const {
	return _finalized;
}

void RootSignature::setShaderInputNameLocation(ShaderInputNameLocationMap &&map) {
	_shaderInputNameLocation = std::move(map);
}

auto RootSignature::getShaderParamLocationByName(const std::string &name) const -> std::optional<ShaderInputNameLocation> {
	auto iter = _shaderInputNameLocation.find(name);
	if (iter != _shaderInputNameLocation.end())
		return iter->second;
	return std::nullopt;
}


size_t RootSignature::getPerTableIndexByRangeType(D3D12_DESCRIPTOR_RANGE_TYPE type) {
	switch (type) {
	case D3D12_DESCRIPTOR_RANGE_TYPE_CBV:
	case D3D12_DESCRIPTOR_RANGE_TYPE_UAV:
	case D3D12_DESCRIPTOR_RANGE_TYPE_SRV:
		return 0;
	case D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER:
		return 1;
	}
	assert(false);
	throw std::runtime_error("invalid D3D12_DESCRIPTOR_RANGE_TYPE");
}


}
