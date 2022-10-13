#pragma once
#include <Dx12lib/Device/Device.h>
#include <Dx12lib/Buffer/UploadBuffer.h>
#include <Dx12lib/Descriptor/DescriptorAllocation.h>
#include <Dx12lib/Resource/ResourceView.hpp>
#include <Dx12lib/Resource/IResource.h>
#include <span>


namespace dx12lib {

// frame resource structured buffer template
template<>
class FRSRStructuredBuffer<RawData> : public ISRStructuredBuffer {
protected:
	FRSRStructuredBuffer(std::weak_ptr<Device> pDevice, const void *pData, size_t numElements, size_t stride);
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const final;
	size_t getBufferSize() const final;
	size_t getElementCount() const final;
	size_t getElementStride() const final;
	void updateBuffer(const void *pData, size_t sizeInByte, size_t offset = 0) final;
	const ShaderResourceView & getSRV() const final;

	template<typename T>
	std::span<T> visit() {
		assert(sizeof(T) == getElementStride());
		size_t frameIndex = FrameIndexProxy::getConstantFrameIndexRef();
		size_t numElements = getElementCount();
		T *ptr = reinterpret_cast<T *>(_pUploadBuffer->getMappedDataByIndex(frameIndex));
		return std::span<T>(ptr, numElements);
	}
private:
	size_t _elementStride;
	ShaderResourceView _srvs[kFrameResourceCount];
	std::unique_ptr<UploadBuffer> _pUploadBuffer;
};


/********************************************************************************************************/

// frame resource structured buffer template
template<typename T>
class FRSRStructuredBuffer : public ISRStructuredBuffer {
protected:
	FRSRStructuredBuffer(std::weak_ptr<Device> pDevice, const T *pData, size_t numElements);
	FRSRStructuredBuffer(std::weak_ptr<Device> pDevice, size_t numElements);
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const final;
	size_t getBufferSize() const final;
	size_t getElementCount() const final;
	size_t getElementStride() const final;
	void updateBuffer(const void *pData, size_t sizeInByte, size_t offset = 0) final;
	const ShaderResourceView & getSRV() const final;
	std::span<T> visit();
private:
	ShaderResourceView _srvs[kFrameResourceCount];
	std::unique_ptr<UploadBuffer> _pUploadBuffer;
};

template <typename T>
FRSRStructuredBuffer<T>::FRSRStructuredBuffer(std::weak_ptr<Device> pDevice, const T *pData, size_t numElements) {
	size_t stride = sizeof(T);
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

template <typename T>
FRSRStructuredBuffer<T>::FRSRStructuredBuffer(std::weak_ptr<Device> pDevice, size_t numElements) 
: FRSRStructuredBuffer(pDevice, nullptr, numElements)
{
}

template <typename T>
WRL::ComPtr<ID3D12Resource> FRSRStructuredBuffer<T>::getD3DResource() const {
	return _pUploadBuffer->getD3DResource();
}

template <typename T>
size_t FRSRStructuredBuffer<T>::getBufferSize() const {
	return _pUploadBuffer->getElementByteSize();
}

template <typename T>
size_t FRSRStructuredBuffer<T>::getElementCount() const {
	return getBufferSize() / sizeof(T);
}

template <typename T>
size_t FRSRStructuredBuffer<T>::getElementStride() const {
	return sizeof(T);
}

template <typename T>
void FRSRStructuredBuffer<T>::updateBuffer(const void *pData, size_t sizeInByte, size_t offset) {
	assert((sizeInByte + offset) <= getElementStride());
	size_t frameIndex = FrameIndexProxy::getConstantFrameIndexRef();
	_pUploadBuffer->copyData(frameIndex, pData, sizeInByte, offset);
}

template <typename T>
const ShaderResourceView & FRSRStructuredBuffer<T>::getSRV() const {
	size_t frameIndex = FrameIndexProxy::getConstantFrameIndexRef();
	return _srvs[frameIndex];
}

template <typename T>
std::span<T> FRSRStructuredBuffer<T>::visit() {
	size_t frameIndex = FrameIndexProxy::getConstantFrameIndexRef();
	size_t numElements = getElementCount();
	T *ptr = reinterpret_cast<T *>(_pUploadBuffer->getMappedDataByIndex(frameIndex));
	return std::span<T>(ptr, numElements);
}

}
