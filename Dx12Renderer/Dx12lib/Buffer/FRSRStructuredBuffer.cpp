#include "FRSRStructuredBuffer.hpp"
#include "Dx12lib/Pipeline/ShaderRegister.hpp"

namespace dx12lib {

FRSRStructuredBuffer<RawData>::FRSRStructuredBuffer(std::weak_ptr<Device> pDevice, const void *pData, size_t numElements, size_t stride)
: _elementStride(stride)
{
	size_t sizeInByte = numElements * stride;
	auto pSharedDevice = pDevice.lock();
	_pUploadBuffer = std::make_unique<UploadBuffer>(
		pDevice,
		kFrameResourceCount,
		sizeInByte,
		false
	);

	D3D12_SHADER_RESOURCE_VIEW_DESC desc = {};
	desc.Format = _pUploadBuffer->getD3DResource()->GetDesc().Format;
	desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	desc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	desc.Buffer.NumElements = static_cast<UINT>(numElements);
	desc.Buffer.StructureByteStride = static_cast<UINT>(stride);
	desc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;

	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, kFrameResourceCount);
	for (size_t i = 0; i < kFrameResourceCount; ++i) {
		if (pData != nullptr)
			_pUploadBuffer->copyData(i, pData, sizeInByte, 0);

		desc.Buffer.FirstElement = i * numElements;
		pSharedDevice->getD3DDevice()->CreateShaderResourceView(
			_pUploadBuffer->getD3DResource().Get(),
			&desc,
			descriptor.getCPUHandle(i)
		);
		_srvs[i] = ShaderResourceView(descriptor, this, i);
	}
}

WRL::ComPtr<ID3D12Resource> FRSRStructuredBuffer<RawData>::getD3DResource() const {
	return _pUploadBuffer->getD3DResource();
}

size_t FRSRStructuredBuffer<RawData>::getBufferSize() const {
	return _pUploadBuffer->getElementByteSize();
}

size_t FRSRStructuredBuffer<RawData>::getElementCount() const {
	return getBufferSize() / _elementStride;
}

size_t FRSRStructuredBuffer<RawData>::getElementStride() const {
	return _elementStride;
}

void FRSRStructuredBuffer<RawData>::updateBuffer(const void *pData, size_t sizeInByte, size_t offset) {
	assert((sizeInByte + offset) <= getElementStride());
	size_t frameIndex = FrameIndexProxy::getFrameResourceIndex();
	_pUploadBuffer->copyData(frameIndex, pData, sizeInByte, offset);
}

const ShaderResourceView & FRSRStructuredBuffer<RawData>::getSRV() const {
	size_t frameIndex = FrameIndexProxy::getFrameResourceIndex();
	return _srvs[frameIndex];
}

}
