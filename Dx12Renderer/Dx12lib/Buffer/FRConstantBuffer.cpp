#include "FRConstantBuffer.hpp"

namespace dx12lib {

FRConstantBuffer<RawData>::FRConstantBuffer(std::weak_ptr<Device> pDevice, size_t sizeInByte, const void *pData) {
	_pObject = std::unique_ptr<BYTE[]>(new BYTE[sizeInByte]);
	if (pData != nullptr)
		std::memcpy(_pObject.get(), pData, sizeInByte);
	else
		std::memset(_pObject.get(), 0, sizeInByte);

	auto pSharedDevice = pDevice.lock();
	_pUploadBuffer = std::make_unique<UploadBuffer>(
		pDevice,
		static_cast<size_t>(kFrameResourceCount),
		sizeInByte,
		true
	);

	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, kFrameResourceCount);
	for (size_t i = 0; i < kFrameResourceCount; ++i) {
		_bufferDirty.set(i, true);
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbv;
		cbv.BufferLocation = _pUploadBuffer->getGPUAddressByIndex(i);
		cbv.SizeInBytes = static_cast<UINT>(UploadBuffer::calcConstantBufferByteSize(sizeInByte));
		pSharedDevice->getD3DDevice()->CreateConstantBufferView(
			&cbv,
			descriptor.getCPUHandle(i)
		);
		_cbvs[i] = ConstantBufferView(descriptor, this, i);
	}
}

WRL::ComPtr<ID3D12Resource> FRConstantBuffer<RawData>::getD3DResource() const {
	return _pUploadBuffer->getD3DResource();
}

size_t FRConstantBuffer<RawData>::getBufferSize() const {
	return _pUploadBuffer->getElementByteSize();
}

size_t FRConstantBuffer<RawData>::getElementStride() const {
	return _pUploadBuffer->getElementByteSize();
}

BYTE *FRConstantBuffer<RawData>::getMappedPtr() {
	size_t frameIndex = FrameIndexProxy::getConstantFrameIndexRef();
	return _pUploadBuffer->getMappedDataByIndex(frameIndex);
}

const BYTE *FRConstantBuffer<RawData>::getMappedPtr() const {
	size_t frameIndex = FrameIndexProxy::getConstantFrameIndexRef();
	return _pUploadBuffer->getMappedDataByIndex(frameIndex);
}

void FRConstantBuffer<RawData>::updateBuffer(const void *pData, size_t sizeInByte, size_t offset) {
	assert((sizeInByte + offset) <= getElementStride());
	std::memcpy(_pObject.get() + offset, pData, sizeInByte);
	_bufferDirty.set(FrameIndexProxy::getConstantFrameIndexRef());
}

const ConstantBufferView & FRConstantBuffer<RawData>::getCBV() const {
	size_t frameIndex = FrameIndexProxy::getConstantFrameIndexRef();
	if (_bufferDirty.test(frameIndex)) {
		_pUploadBuffer->copyData(frameIndex, _pObject.get(), getElementStride(), 0);
		_bufferDirty.set(frameIndex, false);
	}
	return _cbvs[frameIndex];
}

}


