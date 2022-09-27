#include "IRenderTargetResource.h"
#include "Dx12lib/Device/Device.h"
#include <DirectXColors.h>

namespace dx12lib {

IRenderTarget::IRenderTarget() {
	_clearValue.Format = DXGI_FORMAT_UNKNOWN;
	std::memcpy(&_clearValue.Color, &DX::Colors::White, sizeof(_clearValue.Color));
}

D3D12_CLEAR_VALUE IRenderTarget::getClearValue() const {
	return _clearValue;
}

/// *********************************** IRenderTarget2D ****************************************
#if 1
const RenderTargetView & IRenderTarget2D::getRTV(size_t mipSlice) const {
	if (_rtvMgr.exist(mipSlice))
		return _rtvMgr.get(mipSlice);

	auto pResource = getD3DResource();
	auto resourceDesc = pResource->GetDesc();
	assert(mipSlice < resourceDesc.MipLevels);
	auto pSharedDevice = getDevice().lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = resourceDesc.Format;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.PlaneSlice = 0;
	rtvDesc.Texture2D.MipSlice = static_cast<UINT>(mipSlice);

	pSharedDevice->getD3DDevice()->CreateRenderTargetView(
		pResource.Get(),
		&rtvDesc,
		descriptor.getCPUHandle()
	);

	RenderTargetView RTV(descriptor, this);
	_rtvMgr.set(mipSlice, RTV);
	return _rtvMgr.get(mipSlice);
}
#endif

/// *********************************** IRenderTarget2DArray ****************************************
#if 1
const RenderTargetView &IRenderTarget2DArray::getPlaneRTV(size_t planeSlice, size_t mipSlice) const {
	assert(planeSlice < getPlaneSlice());
	ViewManager<RenderTargetView> &planeRtvMgr = _planeRtvMgr[planeSlice];
	if (planeRtvMgr.exist(mipSlice))
		return planeRtvMgr.get(mipSlice);

	auto pResource = getD3DResource();
	auto resourceDesc = pResource->GetDesc();
	auto pSharedDevice = getDevice().lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = resourceDesc.Format;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
	rtvDesc.Texture2DArray.MipSlice = static_cast<UINT>(mipSlice);
	rtvDesc.Texture2DArray.FirstArraySlice = static_cast<UINT>(planeSlice);
	rtvDesc.Texture2DArray.ArraySize = 1;
	rtvDesc.Texture2DArray.PlaneSlice = 0;
	pSharedDevice->getD3DDevice()->CreateRenderTargetView(
		pResource.Get(),
		&rtvDesc,
		descriptor.getCPUHandle()
	);

	RenderTargetView RTV(descriptor, this);
	planeRtvMgr.set(mipSlice, RTV);
	return planeRtvMgr.get(mipSlice);
}
#endif

/// *********************************** IRenderTargetCube ****************************************
#if 1
const RenderTargetView & IRenderTargetCube::getFaceRTV(CubeFace face, size_t mipSlice) const {
	ViewManager<RenderTargetView> &cubeRtvMgr = _cubeRtvMgr[face];
	if (cubeRtvMgr.exist(mipSlice))
		return cubeRtvMgr.get(mipSlice);

	auto pResource = getD3DResource();
	auto resourceDesc = pResource->GetDesc();
	auto pSharedDevice = getDevice().lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = resourceDesc.Format;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
	rtvDesc.Texture2DArray.MipSlice = static_cast<UINT>(mipSlice);
	rtvDesc.Texture2DArray.FirstArraySlice = static_cast<UINT>(face);
	rtvDesc.Texture2DArray.ArraySize = 1;
	rtvDesc.Texture2DArray.PlaneSlice = 0;
	pSharedDevice->getD3DDevice()->CreateRenderTargetView(
		pResource.Get(),
		&rtvDesc,
		descriptor.getCPUHandle()
	);

	RenderTargetView RTV(descriptor, this);
	cubeRtvMgr.set(mipSlice, RTV);
	return cubeRtvMgr.get(mipSlice);
}
#endif
}
