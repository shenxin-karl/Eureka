#include "IUnorderedAccessResource.h"
#include "Dx12lib/Device/Device.h"

namespace dx12lib {

/// *********************************** IUnorderedAccess2D ****************************************
#if 1
const UnorderedAccessView & IUnorderedAccess2D::getUAV(size_t mipSlice) const {
	if (_uavMgr.exist(mipSlice))
		return _uavMgr.get(mipSlice);

	assert(mipSlice < getMipLevels());
	auto pResource = getD3DResource();
	auto pSharedDevice = getDevice().lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
	uavDesc.Format = pResource->GetDesc().Format;
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
	uavDesc.Texture2D.MipSlice = static_cast<UINT>(mipSlice);
	uavDesc.Texture2D.PlaneSlice = 0;
	pSharedDevice->getD3DDevice()->CreateUnorderedAccessView(
		pResource.Get(),
		nullptr,
		&uavDesc,
		descriptor.getCPUHandle()
	);
	UnorderedAccessView UAV(descriptor, this);
	_uavMgr.set(mipSlice, UAV);
	return _uavMgr.get(mipSlice);
}
#endif

/// *********************************** IUnorderedAccess2D ****************************************
#if 1
const UnorderedAccessView & IUnorderedAccess2DArray::getPlaneUAV(size_t planeSlice, size_t mipSlice) const {
	assert(planeSlice < getPlaneSlice());
	ViewManager<UnorderedAccessView> &planeUavMgr = _planeUavMgr[planeSlice];
	if (planeUavMgr.exist(mipSlice))
		return planeUavMgr.get(mipSlice);


	assert(mipSlice < getMipLevels());
	auto pResource = getD3DResource();
	auto pSharedDevice = getDevice().lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
	uavDesc.Format = pResource->GetDesc().Format;
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
	uavDesc.Texture2DArray.MipSlice = static_cast<UINT>(mipSlice);
	uavDesc.Texture2DArray.FirstArraySlice = static_cast<UINT>(planeSlice);
	uavDesc.Texture2DArray.ArraySize = 1;
	uavDesc.Texture2DArray.PlaneSlice = 0;
	pSharedDevice->getD3DDevice()->CreateUnorderedAccessView(
		pResource.Get(),
		nullptr,
		&uavDesc,
		descriptor.getCPUHandle()
	);

	UnorderedAccessView UAV(descriptor, this);
	planeUavMgr.set(mipSlice, UAV);
	return planeUavMgr.get(mipSlice);
}
#endif

/// *********************************** IUnorderedAccessCube ****************************************
#if 1
const UnorderedAccessView & IUnorderedAccessCube::getFaceUAV(CubeFace face, size_t mipSlice) const {
	ViewManager<UnorderedAccessView> &cubeUavMgr = _cubeUavMgr[face];
	if (cubeUavMgr.exist(mipSlice))
		return cubeUavMgr.get(mipSlice);

	assert(mipSlice < getMipLevels());
	auto pResource = getD3DResource();
	auto pSharedDevice = getDevice().lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
	uavDesc.Format = pResource->GetDesc().Format;
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
	uavDesc.Texture2DArray.MipSlice = static_cast<UINT>(mipSlice);
	uavDesc.Texture2DArray.FirstArraySlice = static_cast<UINT>(face);
	uavDesc.Texture2DArray.ArraySize = 1;
	uavDesc.Texture2DArray.PlaneSlice = 0;
	pSharedDevice->getD3DDevice()->CreateUnorderedAccessView(
		pResource.Get(),
		nullptr,
		&uavDesc,
		descriptor.getCPUHandle()
	);

	UnorderedAccessView UAV(descriptor, this);
	cubeUavMgr.set(mipSlice, UAV);
	return cubeUavMgr.get(mipSlice);
}

const UnorderedAccessView & IUnorderedAccessCube::get2DArrayUAV(size_t mipSlice) const {
	if (_2DArrayUavMgr.exist(mipSlice))
		return _2DArrayUavMgr.get(mipSlice);

	assert(mipSlice < getMipLevels());
	auto pResource = getD3DResource();
	auto pSharedDevice = getDevice().lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
	uavDesc.Format = pResource->GetDesc().Format;
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
	uavDesc.Texture2DArray.MipSlice = static_cast<UINT>(mipSlice);
	uavDesc.Texture2DArray.FirstArraySlice = 0;
	uavDesc.Texture2DArray.ArraySize = 6;
	uavDesc.Texture2DArray.PlaneSlice = 0;
	pSharedDevice->getD3DDevice()->CreateUnorderedAccessView(
		pResource.Get(),
		nullptr,
		&uavDesc,
		descriptor.getCPUHandle()
	);

	UnorderedAccessView UAV(descriptor, this);
	_2DArrayUavMgr.set(mipSlice, UAV);
	return _2DArrayUavMgr.get(mipSlice);
}
#endif
}
