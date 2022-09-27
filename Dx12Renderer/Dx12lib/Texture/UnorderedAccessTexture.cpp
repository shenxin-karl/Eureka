#include <Dx12lib/Texture/UnorderedAccessTexture.h>
#include <Dx12lib/Device/Device.h>
#include <Dx12lib/Tool/D3Dx12.h>
#include <Dx12lib/Resource/ResourceStateTracker.h>

namespace dx12lib {

WRL::ComPtr<ID3D12Resource> UnorderedAccess2D::getD3DResource() const {
	return _pResource;
}

UnorderedAccess2D::~UnorderedAccess2D() {
	if (auto pSharedDevice = _pDevice.lock()) {
		if (auto *pGlobalResourceState = pSharedDevice->getGlobalResourceState())
			pGlobalResourceState->removeGlobalResourceState(_pResource.Get());
	}
}

UnorderedAccess2D::UnorderedAccess2D(std::weak_ptr<Device> pDevice, WRL::ComPtr<ID3D12Resource> pResource,
                                     D3D12_RESOURCE_STATES state)
: _pResource(pResource) {
	setDevice(pDevice);
	auto pSharedDevice = pDevice.lock();
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), state);
}

UnorderedAccess2D::UnorderedAccess2D(std::weak_ptr<Device> pDevice, size_t width, size_t height,
	DXGI_FORMAT format)
{
	setDevice(pDevice);
	auto pSharedDevice = pDevice.lock();
	if (format == DXGI_FORMAT_UNKNOWN)
		format = pSharedDevice->getDesc().backBufferFormat;

	D3D12_RESOURCE_DESC unorderedAccessDesc = {};
	unorderedAccessDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	unorderedAccessDesc.Alignment = 0;
	unorderedAccessDesc.Width = width;
	unorderedAccessDesc.Height = static_cast<UINT>(height);
	unorderedAccessDesc.DepthOrArraySize = 1;
	unorderedAccessDesc.Format = format;
	unorderedAccessDesc.MipLevels = 1;
	unorderedAccessDesc.SampleDesc.Count = 1;
	unorderedAccessDesc.SampleDesc.Quality = 0;
	unorderedAccessDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	unorderedAccessDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
	ThrowIfFailed(pSharedDevice->getD3DDevice()->CreateCommittedResource(
		RVPtr(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT)),
		D3D12_HEAP_FLAG_NONE,
		RVPtr(unorderedAccessDesc),
		D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
		nullptr,
		IID_PPV_ARGS(&_pResource)
	));
	
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

WRL::ComPtr<ID3D12Resource> UnorderedAccess2DArray::getD3DResource() const {
	return _pResource;
}

UnorderedAccess2DArray::~UnorderedAccess2DArray() {
	if (auto pSharedDevice = _pDevice.lock()) {
		if (auto *pGlobalResourceState = pSharedDevice->getGlobalResourceState())
			pGlobalResourceState->removeGlobalResourceState(_pResource.Get());
	}
}

UnorderedAccess2DArray::UnorderedAccess2DArray(std::weak_ptr<Device> pDevice, WRL::ComPtr<ID3D12Resource> pResource,
                                               D3D12_RESOURCE_STATES state)
: _pResource(pResource)
{
	setDevice(pDevice);
	auto pSharedDevice = pDevice.lock();
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), state);
}

UnorderedAccess2DArray::UnorderedAccess2DArray(std::weak_ptr<Device> pDevice, size_t width, size_t height,
	size_t planeSlice, DXGI_FORMAT format)
{
	setDevice(pDevice);
	auto pSharedDevice = pDevice.lock();
	if (format == DXGI_FORMAT_UNKNOWN)
		format = pSharedDevice->getDesc().backBufferFormat;

	D3D12_RESOURCE_DESC unorderedAccessDesc = {};
	unorderedAccessDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	unorderedAccessDesc.Alignment = 0;
	unorderedAccessDesc.Width = width;
	unorderedAccessDesc.Height = static_cast<UINT>(height);
	unorderedAccessDesc.DepthOrArraySize = static_cast<UINT>(planeSlice);
	unorderedAccessDesc.MipLevels = 1;
	unorderedAccessDesc.Format = format;
	unorderedAccessDesc.SampleDesc.Count = 1;
	unorderedAccessDesc.SampleDesc.Quality = 0;
	unorderedAccessDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	unorderedAccessDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
	ThrowIfFailed(pSharedDevice->getD3DDevice()->CreateCommittedResource(
		RVPtr(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT)),
		D3D12_HEAP_FLAG_NONE,
		RVPtr(unorderedAccessDesc),
		D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
		nullptr,
		IID_PPV_ARGS(&_pResource)
	));
	
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

WRL::ComPtr<ID3D12Resource> UnorderedAccessCube::getD3DResource() const {
	return _pResource;
}

UnorderedAccessCube::~UnorderedAccessCube() {
	if (auto pSharedDevice = _pDevice.lock()) {
		if (auto *pGlobalResourceState = pSharedDevice->getGlobalResourceState())
			pGlobalResourceState->removeGlobalResourceState(_pResource.Get());
	}
}

UnorderedAccessCube::UnorderedAccessCube(std::weak_ptr<Device> pDevice, WRL::ComPtr<ID3D12Resource> pResource,
                                         D3D12_RESOURCE_STATES state)
: _pResource(pResource)
{
	setDevice(pDevice);
	auto pSharedDevice = pDevice.lock();
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), state);
}

UnorderedAccessCube::UnorderedAccessCube(std::weak_ptr<Device> pDevice, size_t width, size_t height, size_t mipLevels,
	DXGI_FORMAT format)
{
	setDevice(pDevice);
	auto pSharedDevice = pDevice.lock();
	if (format == DXGI_FORMAT_UNKNOWN)
		format = pSharedDevice->getDesc().backBufferFormat;

	D3D12_RESOURCE_DESC unorderedAccessDesc = {};
	unorderedAccessDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	unorderedAccessDesc.Alignment = 0;
	unorderedAccessDesc.Width = width;
	unorderedAccessDesc.Height = static_cast<UINT>(height);
	unorderedAccessDesc.DepthOrArraySize = 6;
	unorderedAccessDesc.MipLevels = static_cast<UINT16>(mipLevels);
	unorderedAccessDesc.Format = format;
	unorderedAccessDesc.SampleDesc.Count = 1;
	unorderedAccessDesc.SampleDesc.Quality = 0;
	unorderedAccessDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	unorderedAccessDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
	ThrowIfFailed(pSharedDevice->getD3DDevice()->CreateCommittedResource(
		RVPtr(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT)),
		D3D12_HEAP_FLAG_NONE,
		&unorderedAccessDesc,
		D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
		nullptr,
		IID_PPV_ARGS(&_pResource)
	));
	
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
}


}
