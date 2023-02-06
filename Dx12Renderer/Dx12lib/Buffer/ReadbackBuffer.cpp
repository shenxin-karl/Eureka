#include "ReadbackBuffer.h"
#include <Dx12lib/Resource/ResourceStateTracker.h>
#include <Dx12lib/Device/Device.h>

namespace dx12lib {

WRL::ComPtr<ID3D12Resource> ReadBackBuffer::getD3DResource() const {
	return _pResource;
}

size_t ReadBackBuffer::getBufferSize() const {
	return _pResource->GetDesc().Width;
}

bool ReadBackBuffer::isCompleted() const {
	return _isCompleted;
}

const void *ReadBackBuffer::getMappedPtr() const {
	if (!_isCompleted) {
		assert(false);
		return nullptr;
	}
	assert(_pMapped != nullptr);
	return _pMapped;
}

size_t ReadBackBuffer::getElementCount() const {
	return getBufferSize() / _elementStride;
}

size_t ReadBackBuffer::getElementStride() const {
	return _elementStride;
}

void ReadBackBuffer::setCompletedCallback(const std::function<void(IReadBackBuffer *)> &callback) {
	_completedCallBack = callback;
}

ReadBackBuffer::~ReadBackBuffer() {
	if (_pMapped != nullptr) {
		_pResource->Unmap(0, nullptr);
		_pMapped = nullptr;
	}
	if (auto pSharedDevice = _pDevice.lock()) {
		if (auto *pGlobalResourceState = pSharedDevice->getGlobalResourceState())
			pGlobalResourceState->removeGlobalResourceState(_pResource.Get());
	}
}

ReadBackBuffer::ReadBackBuffer(std::weak_ptr<Device> pDevice, size_t numElements, size_t stride)
: _elementStride(stride), _pDevice(pDevice)
{
	size_t sizeInByte = numElements * stride;
	ThrowIfFailed(pDevice.lock()->getD3DDevice()->CreateCommittedResource(
		RVPtr(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_READBACK)),
		D3D12_HEAP_FLAG_NONE,
		RVPtr(CD3DX12_RESOURCE_DESC::Buffer(sizeInByte)),
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&_pResource)
	));
	pDevice.lock()->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST);
}

void ReadBackBuffer::setCompleted(bool flag) {
	_isCompleted = flag;
	if (flag) {
		_pResource->Map(0, nullptr, &_pMapped);
		if (_completedCallBack != nullptr)
			_completedCallBack(this);
	}
}

}