#include <Dx12lib/Texture/SamplerTexture.h>
#include <Dx12lib/Resource/ResourceStateTracker.h>
#include <Dx12lib/Device/Device.h>

namespace dx12lib {

WRL::ComPtr<ID3D12Resource> SamplerTexture2D::getD3DResource() const {
	return _pResource;
}

SamplerTexture2D::~SamplerTexture2D() {
	if (auto pSharedDevice = _pDevice.lock()) {
		if (auto *pGlobalResourceState = pSharedDevice->getGlobalResourceState())
			pGlobalResourceState->removeGlobalResourceState(_pResource.Get());
	}
}

SamplerTexture2D::SamplerTexture2D(std::weak_ptr<Device> pDevice, 
	WRL::ComPtr<ID3D12Resource> pResource,
    D3D12_RESOURCE_STATES state)
: _pResource(pResource)
{
	setDevice(pDevice);
	assert(pResource->GetDesc().DepthOrArraySize == 1);
	auto pSharedDevice = pDevice.lock();
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), state);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRL::ComPtr<ID3D12Resource> SamplerTexture2DArray::getD3DResource() const {
	return _pResource;
}


SamplerTexture2DArray::~SamplerTexture2DArray() {
	if (auto pSharedDevice = _pDevice.lock()) {
		if (auto *pGlobalResourceState = pSharedDevice->getGlobalResourceState())
			pGlobalResourceState->removeGlobalResourceState(_pResource.Get());
	}
}

SamplerTexture2DArray::SamplerTexture2DArray(std::weak_ptr<Device> pDevice, 
	WRL::ComPtr<ID3D12Resource> pResource,
    D3D12_RESOURCE_STATES state)
: _pResource(pResource)
{
	setDevice(pDevice);
	assert(pResource->GetDesc().DepthOrArraySize >= 1);
	auto pSharedDevice = pDevice.lock();
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), state);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRL::ComPtr<ID3D12Resource> SamplerTextureCube::getD3DResource() const {
	return _pResource;
}

SamplerTextureCube::~SamplerTextureCube() {
	if (auto pSharedDevice = _pDevice.lock()) {
		if (auto *pGlobalResourceState = pSharedDevice->getGlobalResourceState())
			pGlobalResourceState->removeGlobalResourceState(_pResource.Get());
	}
}

SamplerTextureCube::SamplerTextureCube(std::weak_ptr<Device> pDevice, 
	WRL::ComPtr<ID3D12Resource> pResource,
	D3D12_RESOURCE_STATES state)
:  _pResource(pResource)
{
	setDevice(pDevice);
	assert(pResource->GetDesc().DepthOrArraySize == 6);
	auto pSharedDevice = pDevice.lock();
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), state);
}

}
