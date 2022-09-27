#include "IDepthStencilResource.h"

#include "Dx12lib/Device/Device.h"

namespace dx12lib {

IDepthStencil::IDepthStencil() {
	_clearValue.Format = DXGI_FORMAT_UNKNOWN;
	_clearValue.DepthStencil.Depth = 1.f;
	_clearValue.DepthStencil.Stencil = 0;
}

D3D12_CLEAR_VALUE IDepthStencil::getClearValue() const {
	return _clearValue;
}


/// ************************ IDepthStencil2D ********************************
#if 1
bool IDepthStencil2D::checkSRVState(D3D12_RESOURCE_STATES state) const {
	return state & D3D12_RESOURCE_STATE_DEPTH_READ;
}

const DepthStencilView & IDepthStencil2D::getDSV() const {
	if (_dsv.valid())
		return _dsv;

	auto pResource = getD3DResource();
	auto pSharedDevice = getDevice().lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

	auto resourceDesc = pResource->GetDesc();
	D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	depthStencilViewDesc.Format = getDepthDSVFormat(resourceDesc.Format);
	depthStencilViewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	depthStencilViewDesc.Flags = D3D12_DSV_FLAG_NONE;

	assert(isDepthFormat(depthStencilViewDesc.Format));
	_dsv = DepthStencilView(descriptor, this);
	pSharedDevice->getD3DDevice()->CreateDepthStencilView(
		pResource.Get(),
		&depthStencilViewDesc,
		_dsv.getCPUDescriptorHandle()
	);

	return _dsv;
}
#endif

/// ************************ IDepthStencil2DArray ********************************
#if 1
bool IDepthStencil2DArray::checkSRVState(D3D12_RESOURCE_STATES state) const {
	return state & D3D12_RESOURCE_STATE_DEPTH_READ;
}

const DepthStencilView & IDepthStencil2DArray::getPlaneDSV(size_t planeSlice) const {
	auto iter = _planeDsvMgr.find(planeSlice);
	if (iter != _planeDsvMgr.end())
		return iter->second;

	auto pSharedDevice = getDevice().lock();
	auto pResource = getD3DResource();
	auto resourceDesc = pResource->GetDesc();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = getDepthDSVFormat(resourceDesc.Format);
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DARRAY;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	dsvDesc.Texture2DArray.MipSlice = 0;
	dsvDesc.Texture2DArray.FirstArraySlice = static_cast<UINT>(planeSlice);
	dsvDesc.Texture2DArray.ArraySize = 1;
	pSharedDevice->getD3DDevice()->CreateDepthStencilView(
		pResource.Get(),
		&dsvDesc,
		descriptor.getCPUHandle()
	);

	DepthStencilView dsv(descriptor, this);
	auto &res = (_planeDsvMgr[planeSlice] = dsv);
	return res;
}

#endif
}
