#include <Dx12lib/Buffer/UAStructuredBuffer.h>

#include "Dx12lib/Context/CommandList.h"
#include "Dx12lib/Device/Device.h"

namespace dx12lib {


WRL::ComPtr<ID3D12Resource> UAStructuredBuffer::getD3DResource() const {
	return _pDefaultBuffer->getD3DResource();
}

size_t UAStructuredBuffer::getBufferSize() const {
	return _pDefaultBuffer->getBufferSize();
}

size_t UAStructuredBuffer::getElementCount() const {
	return getBufferSize() / getElementStride();
}

size_t UAStructuredBuffer::getElementStride() const {
	return _elementStride;
}

const UnorderedAccessView & UAStructuredBuffer::getUAV() const {
	return _uav;
}

const ShaderResourceView & UAStructuredBuffer::getSRV() const {
	return _srv;
}

UAStructuredBuffer::UAStructuredBuffer(std::weak_ptr<Device> pDevice, 
	std::shared_ptr<CommandList> pCmdList,
	const void *pData, 
	size_t numElements, 
	size_t stride)
: _elementStride(stride)
{
	assert(numElements > 0);
	assert(stride > 0);
	size_t sizeInByte = numElements * stride;
	auto pSharedDevice = pDevice.lock();
	_pDefaultBuffer = std::make_unique<DefaultBuffer>(
		pDevice,
		pCmdList->getD3DCommandList(),
		pData,
		sizeInByte,
		D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS,
		D3D12_RESOURCE_STATE_UNORDERED_ACCESS
	);

	auto descriptors = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 2);

	// create uav
	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
	uavDesc.Format = DXGI_FORMAT_UNKNOWN;
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.FirstElement = 0;
	uavDesc.Buffer.NumElements = static_cast<UINT>(numElements);
	uavDesc.Buffer.StructureByteStride = static_cast<UINT>(stride);
	uavDesc.Buffer.CounterOffsetInBytes = 0;
	uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
	pSharedDevice->getD3DDevice()->CreateUnorderedAccessView(
		_pDefaultBuffer->getD3DResource().Get(),
		nullptr,
		&uavDesc,
		descriptors.getCPUHandle(0)
	);
	_uav = UnorderedAccessView(descriptors, this, 0);

	// create srv
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Buffer.FirstElement = 0;
	srvDesc.Buffer.NumElements = static_cast<UINT>(numElements);
	srvDesc.Buffer.StructureByteStride = static_cast<UINT>(stride);
	srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	pSharedDevice->getD3DDevice()->CreateShaderResourceView(
		_pDefaultBuffer->getD3DResource().Get(),
		&srvDesc,
		descriptors.getCPUHandle(1)
	);
	_srv = ShaderResourceView(descriptors, this, 1);
}

}
