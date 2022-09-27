#include <Dx12lib/Buffer/ConstantBuffer.h>
#include <Dx12lib/Buffer/UploadBuffer.h>
#include <Dx12lib/Device/Device.h>
#include <Dx12lib/Descriptor/DescriptorAllocation.h>
#include <Dx12lib/Resource/ResourceStateTracker.h>
#include <Dx12lib/Resource/ResourceView.hpp>

namespace dx12lib {

ConstantBuffer::ConstantBuffer(std::weak_ptr<Device> pDevice, const void *pData, size_t sizeInByte) {
	_pUploadBuffer = std::make_unique<UploadBuffer>(
		pDevice,
		1,
		sizeInByte,
		true
	);

	if (pData != nullptr) {
		auto *pMapped = _pUploadBuffer->getMappedDataByIndex(0);
		std::memcpy(pMapped, pData, sizeInByte);
	}

	auto address = _pUploadBuffer->getGPUAddressByIndex(0);
	auto pSharedDevice = pDevice.lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	_constantBufferView = ConstantBufferView(descriptor, this);

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbv;
	cbv.BufferLocation = address;
	cbv.SizeInBytes = static_cast<UINT>(UploadBuffer::calcConstantBufferByteSize(sizeInByte));
	pSharedDevice->getD3DDevice()->CreateConstantBufferView(&cbv, _constantBufferView);
}

WRL::ComPtr<ID3D12Resource> ConstantBuffer::getD3DResource() const {
	return _pUploadBuffer->getD3DResource();
}

size_t ConstantBuffer::getBufferSize() const {
	return _pUploadBuffer->getBufferSize();
}

size_t ConstantBuffer::getElementStride() const {
	return _pUploadBuffer->getElementByteSize();
}

BYTE *ConstantBuffer::getMappedPtr() {
	return _pUploadBuffer->getMappedDataByIndex(0);
}

const BYTE *ConstantBuffer::getMappedPtr() const {
	return _pUploadBuffer->getMappedDataByIndex(0);
}

void ConstantBuffer::updateBuffer(const void *pData, size_t sizeInByte, size_t offset) {
	assert((sizeInByte + offset) < getBufferSize());
	_pUploadBuffer->copyData(0, pData, sizeInByte, offset);
}

const ConstantBufferView & ConstantBuffer::getCBV() const {
	return _constantBufferView;
}


}
