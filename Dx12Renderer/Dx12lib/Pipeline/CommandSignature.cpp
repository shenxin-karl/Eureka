#include "CommandSignature.h"

#include "RootSignature.h"
#include "Dx12lib/Device/Device.h"

namespace dx12lib {

CommandSignature::CommandSignature(std::weak_ptr<Device> pDevice, size_t numParams)
: _pDevice(std::move(pDevice))
{
	reset(numParams);
}

void CommandSignature::destroy() {
	_finalized = false;
	_numParameters = 0;
	_byteStride = 0;
	_pParamArray = nullptr;
	_pCommandSignature = nullptr;
}

void CommandSignature::reset(size_t numParams) {
	_finalized = false;
	_numParameters = numParams;
	_pParamArray = std::make_unique<IndirectParameter[]>(numParams);
}

auto CommandSignature::operator[](size_t index) -> IndirectParameter & {
	return at(index);
}

auto CommandSignature::operator[](size_t index) const -> const IndirectParameter & {
	return at(index);
}

auto CommandSignature::at(size_t index) -> IndirectParameter & {
	assert(index < _numParameters);
	return _pParamArray[index];
}

auto CommandSignature::at(size_t index) const -> const IndirectParameter & {
	assert(index < _numParameters);
	return _pParamArray[index];
}

auto CommandSignature::getByteStride() const -> size_t {
	assert(_finalized);
	return _byteStride;
}

void CommandSignature::finalize(std::shared_ptr<RootSignature> pRootSignature) {
	assert(!_finalized);

	bool requiresRootSignature = false;
	for (size_t i = 0; i < _numParameters; ++i) {
		switch (_pParamArray[i].Type) {
		case D3D12_INDIRECT_ARGUMENT_TYPE_DRAW: 
			_byteStride += sizeof(D3D12_DRAW_ARGUMENTS);
			break;
		case D3D12_INDIRECT_ARGUMENT_TYPE_DRAW_INDEXED: 
			_byteStride += sizeof(D3D12_DRAW_INDEXED_ARGUMENTS);
			break;
		case D3D12_INDIRECT_ARGUMENT_TYPE_DISPATCH: 
			_byteStride += sizeof(D3D12_DISPATCH_ARGUMENTS);
			break;
		case D3D12_INDIRECT_ARGUMENT_TYPE_VERTEX_BUFFER_VIEW:
			_byteStride += sizeof(D3D12_VERTEX_BUFFER_VIEW);
			break;
		case D3D12_INDIRECT_ARGUMENT_TYPE_INDEX_BUFFER_VIEW:
			_byteStride += sizeof(D3D12_INDEX_BUFFER_VIEW);
			break;
		case D3D12_INDIRECT_ARGUMENT_TYPE_CONSTANT:
			_byteStride += _pParamArray[i].Constant.Num32BitValuesToSet * 4;
			requiresRootSignature = true;
			break;
		case D3D12_INDIRECT_ARGUMENT_TYPE_CONSTANT_BUFFER_VIEW: 
		case D3D12_INDIRECT_ARGUMENT_TYPE_SHADER_RESOURCE_VIEW: 
		case D3D12_INDIRECT_ARGUMENT_TYPE_UNORDERED_ACCESS_VIEW: 
			_byteStride += 8;
			requiresRootSignature = true;
			break;
		default:
			assert(false);
			break;;
		}
	}

	D3D12_COMMAND_SIGNATURE_DESC commandSignatureDesc;
	commandSignatureDesc.ByteStride = static_cast<UINT>(_byteStride);
	commandSignatureDesc.NumArgumentDescs = static_cast<UINT>(_numParameters);
	commandSignatureDesc.pArgumentDescs = _pParamArray.get();
	commandSignatureDesc.NodeMask = 1;

	Microsoft::WRL::ComPtr<ID3DBlob> pOutBlob, pErrorBlob;
	ID3D12RootSignature *pRootSig = pRootSignature ? pRootSignature->getRootSignature().Get() : nullptr;
	if (requiresRootSignature)
		assert(pRootSig != nullptr);

	auto pSharedDevice = _pDevice.lock();
	ThrowIfFailed(pSharedDevice->getD3DDevice()->CreateCommandSignature(
		&commandSignatureDesc,
		pRootSig,
		IID_PPV_ARGS(&_pCommandSignature)
	));
	_pCommandSignature->SetName(L"CommandSignature");
	_finalized = true;
}

}
