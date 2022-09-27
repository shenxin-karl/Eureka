#include <Dx12lib/Texture/RenderTargetTexture.h>
#include <Dx12lib/Device/Device.h>
#include <Dx12lib/Resource/ResourceStateTracker.h>

namespace dx12lib {

WRL::ComPtr<ID3D12Resource> RenderTarget2D::getD3DResource() const {
	return _pResource;
}

RenderTarget2D::~RenderTarget2D() {
	if (auto pSharedDevice = _pDevice.lock()) {
		if (auto *pGlobalResourceState = pSharedDevice->getGlobalResourceState())
			pGlobalResourceState->removeGlobalResourceState(_pResource.Get());
	}
}

RenderTarget2D::RenderTarget2D(std::weak_ptr<Device> 
	pDevice, WRL::ComPtr<ID3D12Resource> pResource,
	D3D12_RESOURCE_STATES state, 
	const D3D12_CLEAR_VALUE *pClearValue)
: _pResource(pResource)
{
	setDevice(pDevice);
	if (pClearValue != nullptr)
		_clearValue = *pClearValue;
	else
		_clearValue.Format = pResource->GetDesc().Format;

	auto pSharedDevice = pDevice.lock();
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), state);
}

RenderTarget2D::RenderTarget2D(std::weak_ptr<Device> pDevice, size_t width, size_t height,
	const D3D12_CLEAR_VALUE *pClearValue)
{
	setDevice(pDevice);
	auto pSharedDevice = pDevice.lock();
	if (pClearValue == nullptr) {
		_clearValue.Format = pSharedDevice->getDesc().backBufferFormat;
		pClearValue = &_clearValue;
	} else {
		assert(pClearValue->Format != DXGI_FORMAT_UNKNOWN);
		_clearValue = *pClearValue;
	}

	D3D12_RESOURCE_DESC renderTargetDesc;
	renderTargetDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	renderTargetDesc.Alignment = 0;
	renderTargetDesc.Width = width;
	renderTargetDesc.Height = static_cast<UINT>(height);
	renderTargetDesc.DepthOrArraySize = 1;
	renderTargetDesc.MipLevels = 1;
	renderTargetDesc.Format = pClearValue->Format;
	renderTargetDesc.SampleDesc.Count = 1;
	renderTargetDesc.SampleDesc.Quality = 0;
	renderTargetDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	renderTargetDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
	ThrowIfFailed(pSharedDevice->getD3DDevice()->CreateCommittedResource(
		RVPtr(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT)),
		D3D12_HEAP_FLAG_NONE,
		RVPtr(renderTargetDesc),
		D3D12_RESOURCE_STATE_COMMON,
		pClearValue,
		IID_PPV_ARGS(&_pResource)
	));
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), D3D12_RESOURCE_STATE_COMMON);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRL::ComPtr<ID3D12Resource> RenderTarget2DArray::getD3DResource() const {
	return _pResource;
}

RenderTarget2DArray::~RenderTarget2DArray() {
	if (auto pSharedDevice = _pDevice.lock()) {
		if (auto *pGlobalResourceState = pSharedDevice->getGlobalResourceState())
			pGlobalResourceState->removeGlobalResourceState(_pResource.Get());
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

RenderTarget2DArray::RenderTarget2DArray(std::weak_ptr<Device> pDevice, 
	WRL::ComPtr<ID3D12Resource> pResource,
	D3D12_RESOURCE_STATES state)
: _pResource(pResource)
{
	setDevice(pDevice);
	auto pSharedDevice = pDevice.lock();
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(pResource.Get(), state);
}

RenderTarget2DArray::RenderTarget2DArray(std::weak_ptr<Device> pDevice, 
	size_t width, 
	size_t height, 
	size_t planeSlice,
	const D3D12_CLEAR_VALUE *pClearValue)
{
	setDevice(pDevice);
	assert(planeSlice >= 1);
	auto pSharedDevice = pDevice.lock();
	if (pClearValue == nullptr) {
		_clearValue.Format = pSharedDevice->getDesc().backBufferFormat;
		pClearValue = &_clearValue;
	} else {
		assert(pClearValue->Format != DXGI_FORMAT_UNKNOWN);
		_clearValue = *pClearValue;
	}

	D3D12_RESOURCE_DESC renderTargetDesc;
	renderTargetDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	renderTargetDesc.Alignment = 0;
	renderTargetDesc.Width = width;
	renderTargetDesc.Height = static_cast<UINT>(height);
	renderTargetDesc.DepthOrArraySize = static_cast<UINT16>(planeSlice);
	renderTargetDesc.MipLevels = 1;
	renderTargetDesc.Format = pClearValue->Format;
	renderTargetDesc.SampleDesc.Count = 1;
	renderTargetDesc.SampleDesc.Quality = 0;
	renderTargetDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	renderTargetDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
	ThrowIfFailed(pSharedDevice->getD3DDevice()->CreateCommittedResource(
		RVPtr(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT)),
		D3D12_HEAP_FLAG_NONE,
		RVPtr(renderTargetDesc),
		D3D12_RESOURCE_STATE_COMMON,
		pClearValue,
		IID_PPV_ARGS(&_pResource)
	));

	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), D3D12_RESOURCE_STATE_COMMON);
}

WRL::ComPtr<ID3D12Resource> RenderTargetCube::getD3DResource() const {
	return _pResource;
}


RenderTargetCube::~RenderTargetCube() {
	if (auto pSharedDevice = getDevice().lock()) {
		if (auto *pGlobalResourceState = pSharedDevice->getGlobalResourceState())
			pGlobalResourceState->removeGlobalResourceState(_pResource.Get());
	}
}

RenderTargetCube::RenderTargetCube(std::weak_ptr<Device> pDevice,
	WRL::ComPtr<ID3D12Resource> pResource,
	D3D12_RESOURCE_STATES state)
:  _pResource(pResource)
{
	setDevice(pDevice);
	auto pSharedDevice = pDevice.lock();
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), state);
}

RenderTargetCube::RenderTargetCube(std::weak_ptr<Device> pDevice, size_t width, size_t height,
	D3D12_CLEAR_VALUE *pClearValue)
{
	setDevice(pDevice);
	auto pSharedDevice = pDevice.lock();
	if (pClearValue == nullptr) {
		_clearValue.Format = pSharedDevice->getDesc().backBufferFormat;
		pClearValue = &_clearValue;
	} else {
		assert(pClearValue->Format != DXGI_FORMAT_UNKNOWN);
		_clearValue = *pClearValue;
	}

	D3D12_RESOURCE_DESC renderTargetDesc;
	renderTargetDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	renderTargetDesc.Alignment = 0;
	renderTargetDesc.Width = width;
	renderTargetDesc.Height = static_cast<UINT>(height);
	renderTargetDesc.DepthOrArraySize = 6;
	renderTargetDesc.MipLevels = 1;
	renderTargetDesc.Format = pClearValue->Format;
	renderTargetDesc.SampleDesc.Count = 1;
	renderTargetDesc.SampleDesc.Quality = 0;
	renderTargetDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	renderTargetDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
	ThrowIfFailed(pSharedDevice->getD3DDevice()->CreateCommittedResource(
		RVPtr(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT)),
		D3D12_HEAP_FLAG_NONE,
		RVPtr(renderTargetDesc),
		D3D12_RESOURCE_STATE_COMMON,
		pClearValue,
		IID_PPV_ARGS(&_pResource)
	));
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), D3D12_RESOURCE_STATE_COMMON);
}

}
