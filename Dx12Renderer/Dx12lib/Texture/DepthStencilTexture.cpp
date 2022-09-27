#include <Dx12lib/Texture/DepthStencilTexture.h>
#include <Dx12lib/Resource/ResourceStateTracker.h>
#include <Dx12lib/Device/Device.h>


namespace dx12lib {
/// DepthStencil2D
#if 1
WRL::ComPtr<ID3D12Resource> DepthStencil2D::getD3DResource() const {
	return _pResource;
}

DepthStencil2D::~DepthStencil2D() {
	if (auto pSharedDevice = getDevice().lock()) {
		if (auto *pGlobalResourceState = pSharedDevice->getGlobalResourceState())
			pGlobalResourceState->removeGlobalResourceState(_pResource.Get());
	}
}

DepthStencil2D::DepthStencil2D(std::weak_ptr<Device> pDevice, 
	size_t width,
	size_t height,
	const D3D12_CLEAR_VALUE *pClearValue)
{
	setDevice(pDevice);
	auto pSharedDevice = pDevice.lock();
	DXGI_FORMAT depthStencilFormat = (pClearValue != nullptr) ? pClearValue->Format : DXGI_FORMAT_UNKNOWN;
	if (depthStencilFormat == DXGI_FORMAT_UNKNOWN)
		depthStencilFormat = pSharedDevice->getDesc().depthStencilFormat;

	if (pClearValue == nullptr)
		_clearValue.Format = depthStencilFormat;
	else
		_clearValue = *pClearValue;


	auto typelessFormat = getTypelessFormat(depthStencilFormat);

	assert(_clearValue.Format != DXGI_FORMAT_UNKNOWN);
	pClearValue = &_clearValue;
	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = width;
	depthStencilDesc.Height = static_cast<UINT>(height);
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.Format = typelessFormat;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	ThrowIfFailed(pDevice.lock()->getD3DDevice()->CreateCommittedResource(
		RVPtr(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT)),
		D3D12_HEAP_FLAG_NONE,
		RVPtr(depthStencilDesc),
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		pClearValue,
		IID_PPV_ARGS(&_pResource)
	));

	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), D3D12_RESOURCE_STATE_DEPTH_WRITE);
}

#endif

/// DepthStencil2DArray
#if 1
WRL::ComPtr<ID3D12Resource> DepthStencil2DArray::getD3DResource() const {
	return _pResource;
}

DepthStencil2DArray::~DepthStencil2DArray() {
	if (auto pSharedDevice = getDevice().lock()) {
		if (auto *pGlobalResource = pSharedDevice->getGlobalResourceState())
			pGlobalResource->removeGlobalResourceState(_pResource.Get());
	}
}

DepthStencil2DArray::DepthStencil2DArray(std::weak_ptr<Device> pDevice, 
	size_t width, 
	size_t height, 
	size_t planeSize,
	const D3D12_CLEAR_VALUE *pClearValue)
{
	setDevice(pDevice);
	auto pSharedDevice = pDevice.lock();
	if (pClearValue == nullptr) {
		_clearValue.Format = pSharedDevice->getDesc().depthStencilFormat;
		pClearValue = &_clearValue;
	} else {
		assert(pClearValue->Format != DXGI_FORMAT_UNKNOWN);
		_clearValue = *pClearValue;
	}

	auto typelessFormat = getTypelessFormat(_clearValue.Format);

	D3D12_RESOURCE_DESC depthStencilDesc{};
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = width;
	depthStencilDesc.Height = static_cast<UINT>(height);
	depthStencilDesc.DepthOrArraySize = static_cast<UINT16>(planeSize);
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.Format = typelessFormat;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	ThrowIfFailed(pSharedDevice->getD3DDevice()->CreateCommittedResource(
		RVPtr(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT)),
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		pClearValue,
		IID_PPV_ARGS(&_pResource)
	));

	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), D3D12_RESOURCE_STATE_DEPTH_WRITE);
}

#endif
}
