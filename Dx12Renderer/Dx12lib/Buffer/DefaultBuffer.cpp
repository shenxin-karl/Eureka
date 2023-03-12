#include <Dx12lib/Buffer/DefaultBuffer.h>
#include <Dx12lib/Resource/ResourceStateTracker.h>

#include "Dx12lib/Context/CommonContext.h"
#include "Dx12lib/Device/Device.h"

namespace dx12lib {

DefaultBuffer::DefaultBuffer(std::weak_ptr<Device> pDevice,
	ID3D12GraphicsCommandList *pCmdList,
	const void *pData,
	size_t sizeInByte,
	D3D12_RESOURCE_FLAGS flags,
	D3D12_RESOURCE_STATES finalState)
: _pDevice(pDevice) 
{

	auto pSharedDevice = pDevice.lock();
	auto pD3DDevice = pSharedDevice->getD3DDevice();
	assert(pD3DDevice != nullptr && "createDefaultBuffer pDevice is nullptr");
	bool parameterCorrect = (pCmdList == nullptr && pData == nullptr) || pCmdList != nullptr;
	assert(parameterCorrect && "createDefaultBuffer pCmdList is nullptr");

	ThrowIfFailed(pD3DDevice->CreateCommittedResource(
		RVPtr(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT)),
		D3D12_HEAP_FLAG_NONE,
		RVPtr(CD3DX12_RESOURCE_DESC::Buffer(sizeInByte, flags)),
		finalState,
		nullptr,
		IID_PPV_ARGS(&_pDefaultResource)
	));

	if (pData != nullptr) {
		uploadData(pCmdList, pData, sizeInByte);
	}

	if (auto *pGlobalResourceState = pSharedDevice->getGlobalResourceState()) {
		pGlobalResourceState->addResourceState(_pDefaultResource.Get(), finalState);
	}
}


DefaultBuffer::~DefaultBuffer() {
	if (auto pSharedDevice = _pDevice.lock()) {
		if (auto *pGlobalResourceState = pSharedDevice->getGlobalResourceState())
			pGlobalResourceState->removeResourceState(_pDefaultResource.Get());
	}
}

auto DefaultBuffer::getAddress() const -> D3D12_GPU_VIRTUAL_ADDRESS {
	return _pDefaultResource->GetGPUVirtualAddress();
}

auto DefaultBuffer::getD3DResource() const -> WRL::ComPtr<ID3D12Resource> {
	return _pDefaultResource;
}

auto DefaultBuffer::getBufferType() const -> BufferType {
	return BufferType::DefaultBuffer;
}

auto DefaultBuffer::getBufferSize() const -> size_t {
	return _pDefaultResource->GetDesc().Width;
}

void DefaultBuffer::uploadData(ID3D12GraphicsCommandList *pCmdList, const void *pData, size_t sizeInByte) {
	auto pSharedDevice = _pDevice.lock();
	auto pD3DDevice = pSharedDevice->getD3DDevice();
	auto finalState = pSharedDevice->getGlobalResourceState()->getResourceState(_pDefaultResource.Get());

	// create upload heap
	ThrowIfFailed(pD3DDevice->CreateCommittedResource(
		RVPtr(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD)),
		D3D12_HEAP_FLAG_NONE,
		RVPtr(CD3DX12_RESOURCE_DESC::Buffer(sizeInByte)),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_pUploaderResource)
	));


	// describes the data we want to copy to the default buffer
	D3D12_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pData = pData;
	subResourceData.RowPitch = sizeInByte;
	subResourceData.SlicePitch = subResourceData.RowPitch;

	// copy the data to upload heap using the UpdateResources function
	pCmdList->ResourceBarrier(1, RVPtr(CD3DX12_RESOURCE_BARRIER::Transition(
		_pDefaultResource.Get(),
		finalState,
		D3D12_RESOURCE_STATE_COPY_DEST
	)));

	UpdateSubresources(pCmdList,
		_pDefaultResource.Get(),
		_pUploaderResource.Get(),
		0,
		0,
		1,
		&subResourceData
	);

	pCmdList->ResourceBarrier(1, RVPtr(CD3DX12_RESOURCE_BARRIER::Transition(
		_pDefaultResource.Get(),
		D3D12_RESOURCE_STATE_COPY_DEST,
		finalState
	)));
}

}
