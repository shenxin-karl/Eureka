#include "Texture.h"
#include "Dx12lib/Device/Device.h"
#include "Dx12lib/Resource/ITextureResource.h"
#include "Dx12lib/Resource/ResourceStateTracker.h"

namespace dx12lib {

static ShaderResourceView	InvalidSRV;
static UnorderedAccessView	InvalidUAV;
static RenderTargetView		InvalidRTV;
static DepthStencilView		InvalidDSV;

Texture::Texture(std::weak_ptr<Device> pDevice, const D3D12_RESOURCE_DESC &desc,
	const D3D12_CLEAR_VALUE *pClearValue)
{
	_resourceDesc = desc;
	setDevice(pDevice);
	initClearValue(pClearValue);

	assert(getDimension() != TextureDimension::UNKNOWN);
	if (desc.Flags & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
		const_cast<D3D12_RESOURCE_DESC &>(desc).Format = getTypelessFormat(desc.Format);

	pClearValue = nullptr;
	if (desc.Flags & D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET || desc.Flags & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
		pClearValue = &_clearValue;

	auto pSharedDevice = pDevice.lock();
	auto pd3dDevice = pSharedDevice->getD3DDevice();
	ThrowIfFailed(pd3dDevice->CreateCommittedResource(
		RVPtr(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT)),
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_COMMON,
		pClearValue,
		IID_PPV_ARGS(&_pResource)
	));

	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), D3D12_RESOURCE_STATE_COMMON);
	initFeatureSupport(pd3dDevice, desc.Format);
}

Texture::Texture(std::weak_ptr<Device> pDevice, 
	WRL::ComPtr<ID3D12Resource> pResource,
	D3D12_RESOURCE_STATES state,
	const D3D12_CLEAR_VALUE *pClearValue)
: _pResource(pResource)
{
	setDevice(pDevice);
	_resourceDesc = pResource->GetDesc();
	initClearValue(pClearValue);
	auto pSharedDevice = pDevice.lock();
	pSharedDevice->getGlobalResourceState()->addGlobalResourceState(_pResource.Get(), state);
	initFeatureSupport(pSharedDevice->getD3DDevice(), _resourceDesc.Format);
}

auto Texture::getD3DResource() const -> WRL::ComPtr<ID3D12Resource> {
	return _pResource;
}

auto Texture::getDimension() const -> TextureDimension {
	switch (_resourceDesc.Dimension) {
	case D3D12_RESOURCE_DIMENSION_TEXTURE1D: 
		return TextureDimension::TEXTURE_1D;
	case D3D12_RESOURCE_DIMENSION_TEXTURE2D: 
		return TextureDimension::TEXTURE_2D;
	case D3D12_RESOURCE_DIMENSION_TEXTURE3D: 
		return TextureDimension::TEXTURE_3D;
	case D3D12_RESOURCE_DIMENSION_UNKNOWN: 
	case D3D12_RESOURCE_DIMENSION_BUFFER: 
	default: 
		return TextureDimension::UNKNOWN;
	}
}

auto Texture::getDesc() const -> const D3D12_RESOURCE_DESC & {
	return _resourceDesc;
}

auto Texture::getArraySize() const -> size_t {
	return _resourceDesc.DepthOrArraySize;
}

auto Texture::get2dSRV(size_t mipSlice) const -> const ShaderResourceView & {
	if (mipSlice >= _resourceDesc.MipLevels || getDepthOrArraySize() != 1 || !checkSRVSupport()) {
		assert(false);
		return InvalidSRV;
	}

	ViewKey viewKey;
	viewKey.dimension = ViewDimension::VD_2D;
	viewKey.viewType = ViewType::SRV;
	viewKey.mipSlice = mipSlice;
	if (auto iter = _viewMap.find(viewKey); iter != _viewMap.end())
		return std::get<ShaderResourceView>(iter->second);

	auto pSharedDevice = getDevice().lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	auto pResource = getD3DResource();
	auto resourceDesc = pResource->GetDesc();
	DXGI_FORMAT format = resourceDesc.Format;
	if (resourceDesc.Flags & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
		format = getDepthSRVFormat(format);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;
	srvDesc.Texture2D.PlaneSlice = 0;
	srvDesc.Texture2D.ResourceMinLODClamp = static_cast<float>(mipSlice);

	pSharedDevice->getD3DDevice()->CreateShaderResourceView(
		pResource.Get(),
		&srvDesc,
		descriptor.getCPUHandle()
	);

	ShaderResourceView SRV(descriptor, this);
	return std::get<ShaderResourceView>(_viewMap[viewKey] = SRV);
}

auto Texture::get2dUAV(size_t mipSlice) const -> const UnorderedAccessView & {
	if (mipSlice >= _resourceDesc.MipLevels || getDepthOrArraySize() != 1 || !checkUAVSupport()) {
		assert(false);
		return InvalidUAV;
	}

	ViewKey viewKey;
	viewKey.dimension = ViewDimension::VD_2D;
	viewKey.viewType = ViewType::UAV;
	viewKey.mipSlice = mipSlice;
	if (auto iter = _viewMap.find(viewKey); iter != _viewMap.end())
		return std::get<UnorderedAccessView>(iter->second);

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
	return std::get<UnorderedAccessView>(_viewMap[viewKey] = UAV);
}

auto Texture::get2dRTV(size_t mipSlice) const -> const RenderTargetView & {
	if (mipSlice >= _resourceDesc.MipLevels || getDepthOrArraySize() != 1 || !checkRTVSupport())
		return InvalidRTV;

	ViewKey viewKey;
	viewKey.dimension = ViewDimension::VD_2D;
	viewKey.viewType = ViewType::RTV;
	viewKey.mipSlice = mipSlice;
	if (auto iter = _viewMap.find(viewKey); iter != _viewMap.end())
		return std::get<RenderTargetView>(iter->second);

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
	return std::get<RenderTargetView>(_viewMap[viewKey] = RTV);
}

auto Texture::get2dDSV(size_t mipSlice) const -> const DepthStencilView & {
	if (mipSlice >= _resourceDesc.MipLevels || getDepthOrArraySize() != 1 || !checkDSVSupport())
		return InvalidDSV;

	ViewKey viewKey;
	viewKey.dimension = ViewDimension::VD_2D;
	viewKey.viewType = ViewType::DSV;
	viewKey.mipSlice = mipSlice;
	if (auto iter = _viewMap.find(viewKey); iter != _viewMap.end())
		return std::get<DepthStencilView>(iter->second);

	auto pResource = getD3DResource();
	auto pSharedDevice = getDevice().lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

	auto resourceDesc = pResource->GetDesc();
	D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	depthStencilViewDesc.Format = getDepthDSVFormat(resourceDesc.Format);
	depthStencilViewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = static_cast<UINT>(mipSlice);
	depthStencilViewDesc.Flags = D3D12_DSV_FLAG_NONE;
	assert(isDepthFormat(depthStencilViewDesc.Format));
	DepthStencilView DSV(descriptor, this);
	pSharedDevice->getD3DDevice()->CreateDepthStencilView(
		pResource.Get(),
		&depthStencilViewDesc,
		DSV.getCPUDescriptorHandle()
	);
	return std::get<DepthStencilView>(_viewMap[viewKey] = DSV);
}

auto Texture::getPlaneSRV(size_t planeSlice, size_t mipSlice) const -> const ShaderResourceView & {
	if (mipSlice >= _resourceDesc.MipLevels || planeSlice >= getDepthOrArraySize() || !checkSRVSupport())
		return InvalidSRV;

	ViewKey viewKey;
	viewKey.dimension = ViewDimension::VD_ARRAY;
	viewKey.viewType = ViewType::SRV;
	viewKey.mipSlice = mipSlice;
	viewKey.first = planeSlice;
	if (auto iter = _viewMap.find(viewKey); iter != _viewMap.end())
		return std::get<ShaderResourceView>(iter->second);

	auto pSharedDevice = getDevice().lock();
	auto resourceDesc = _pResource->GetDesc();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	DXGI_FORMAT format = resourceDesc.Format;
	if (resourceDesc.Flags & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
		format = getDepthSRVFormat(format);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Texture2DArray.MostDetailedMip = 0;
	srvDesc.Texture2DArray.MipLevels = -1;
	srvDesc.Texture2DArray.FirstArraySlice = static_cast<UINT>(planeSlice);
	srvDesc.Texture2DArray.ArraySize = 1;
	srvDesc.Texture2DArray.PlaneSlice = 0;
	srvDesc.Texture2DArray.ResourceMinLODClamp = static_cast<float>(mipSlice);
	pSharedDevice->getD3DDevice()->CreateShaderResourceView(
		_pResource.Get(),
		&srvDesc,
		descriptor.getCPUHandle()
	);

	ShaderResourceView SRV(descriptor, this);
	return std::get<ShaderResourceView>(_viewMap[viewKey] = SRV);
}

auto Texture::getPlaneUAV(size_t planeSlice, size_t mipSlice) const -> const UnorderedAccessView & {
	if (mipSlice >= _resourceDesc.MipLevels || planeSlice >= getDepthOrArraySize() || !checkUAVSupport())
		return InvalidUAV;

	ViewKey viewKey;
	viewKey.dimension = ViewDimension::VD_ARRAY;
	viewKey.viewType = ViewType::UAV;
	viewKey.mipSlice = mipSlice;
	viewKey.first = planeSlice;
	if (auto iter = _viewMap.find(viewKey); iter != _viewMap.end())
		return std::get<UnorderedAccessView>(iter->second);

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
	return std::get<UnorderedAccessView>(_viewMap[viewKey] = UAV);
}

auto Texture::getPlaneRTV(size_t planeSlice, size_t mipSlice) const -> const RenderTargetView & {
	if (mipSlice >= _resourceDesc.MipLevels || planeSlice >= getDepthOrArraySize() || !checkRTVSupport())
		return InvalidRTV;

	ViewKey viewKey;
	viewKey.dimension = ViewDimension::VD_ARRAY;
	viewKey.viewType = ViewType::RTV;
	viewKey.mipSlice = mipSlice;
	viewKey.first = planeSlice;
	if (auto iter = _viewMap.find(viewKey); iter != _viewMap.end())
		return std::get<RenderTargetView>(iter->second);

	auto pSharedDevice = getDevice().lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = _resourceDesc.Format;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
	rtvDesc.Texture2DArray.MipSlice = static_cast<UINT>(mipSlice);
	rtvDesc.Texture2DArray.FirstArraySlice = static_cast<UINT>(planeSlice);
	rtvDesc.Texture2DArray.ArraySize = 1;
	rtvDesc.Texture2DArray.PlaneSlice = 0;
	pSharedDevice->getD3DDevice()->CreateRenderTargetView(
		_pResource.Get(),
		&rtvDesc,
		descriptor.getCPUHandle()
	);

	RenderTargetView RTV(descriptor, this);
	return std::get<RenderTargetView>(_viewMap[viewKey] = RTV);
}

auto Texture::getPlaneDSV(size_t planeSlice, size_t mipSlice) const -> const DepthStencilView & {
	if (mipSlice >= _resourceDesc.MipLevels || planeSlice >= getDepthOrArraySize() || !checkDSVSupport())
		return InvalidDSV;

	ViewKey viewKey;
	viewKey.dimension = ViewDimension::VD_ARRAY;
	viewKey.viewType = ViewType::DSV;
	viewKey.mipSlice = mipSlice;
	viewKey.first = planeSlice;
	if (auto iter = _viewMap.find(viewKey); iter != _viewMap.end())
		return std::get<DepthStencilView>(iter->second);

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

	DepthStencilView DSV(descriptor, this);
	return std::get<DepthStencilView>(_viewMap[viewKey] = DSV);
}

auto Texture::getCubeSRV(size_t mipSlice) const -> const ShaderResourceView & {
	if (mipSlice >= _resourceDesc.MipLevels || getDepthOrArraySize() != 6 || !checkSRVSupport()) {
		assert(false);
		return InvalidSRV;
	}

	ViewKey viewKey;
	viewKey.dimension = ViewDimension::VD_CUBE;
	viewKey.viewType = ViewType::SRV;
	viewKey.mipSlice = mipSlice;
	if (auto iter = _viewMap.find(viewKey); iter != _viewMap.end())
		return std::get<ShaderResourceView>(iter->second);

	assert(mipSlice < _resourceDesc.MipLevels);
	auto pSharedDevice = getDevice().lock();

	DXGI_FORMAT format = _resourceDesc.Format;
	if (_resourceDesc.Flags & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
		format = getDepthSRVFormat(format);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
	srvDesc.TextureCube.MipLevels = -1;
	srvDesc.TextureCube.MostDetailedMip = 0;
	srvDesc.TextureCube.ResourceMinLODClamp = static_cast<float>(mipSlice);

	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	pSharedDevice->getD3DDevice()->CreateShaderResourceView(
		_pResource.Get(),
		&srvDesc,
		descriptor.getCPUHandle()
	);

	ShaderResourceView SRV(descriptor, this);
	return std::get<ShaderResourceView>(_viewMap[viewKey] = SRV);
}

auto Texture::getArraySRV(size_t mipSlice) const -> const ShaderResourceView & {
	if (mipSlice >= _resourceDesc.MipLevels || getDepthOrArraySize() <= 1 || !checkSRVSupport())
		return InvalidSRV;

	ViewKey viewKey;
	viewKey.dimension = ViewDimension::VD_ARRAY;
	viewKey.viewType = ViewType::SRV;
	viewKey.mipSlice = mipSlice;
	if (auto iter = _viewMap.find(viewKey); iter != _viewMap.end())
		return std::get<ShaderResourceView>(iter->second);

	assert(mipSlice < _resourceDesc.MipLevels);
	auto pSharedDevice = getDevice().lock();

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = _resourceDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
	srvDesc.Texture2DArray.MipLevels = -1;
	srvDesc.Texture2DArray.PlaneSlice = 0;
	srvDesc.Texture2DArray.MostDetailedMip = 0;
	srvDesc.Texture2DArray.ResourceMinLODClamp = static_cast<float>(mipSlice);
	srvDesc.Texture2DArray.FirstArraySlice = 0;
	srvDesc.Texture2DArray.ArraySize = _resourceDesc.DepthOrArraySize;

	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	pSharedDevice->getD3DDevice()->CreateShaderResourceView(
		_pResource.Get(),
		&srvDesc,
		descriptor.getCPUHandle()
	);

	ShaderResourceView SRV(descriptor, this);
	return std::get<ShaderResourceView>(_viewMap[viewKey] = SRV);
}

auto Texture::getArrayUAV(size_t mipSlice) const -> const UnorderedAccessView & {
	if (mipSlice >= _resourceDesc.MipLevels || getDepthOrArraySize() <= 1 || !checkUAVSupport())
		return InvalidUAV;

	ViewKey viewKey;
	viewKey.dimension = ViewDimension::VD_ARRAY;
	viewKey.viewType = ViewType::UAV;
	viewKey.mipSlice = mipSlice;
	if (auto iter = _viewMap.find(viewKey); iter != _viewMap.end())
		return std::get<UnorderedAccessView>(iter->second);

	assert(mipSlice < getMipLevels());
	auto pResource = getD3DResource();
	auto pSharedDevice = getDevice().lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
	uavDesc.Format = pResource->GetDesc().Format;
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
	uavDesc.Texture2DArray.MipSlice = static_cast<UINT>(mipSlice);
	uavDesc.Texture2DArray.FirstArraySlice = 0;
	uavDesc.Texture2DArray.ArraySize = _resourceDesc.DepthOrArraySize;
	uavDesc.Texture2DArray.PlaneSlice = 0;
	pSharedDevice->getD3DDevice()->CreateUnorderedAccessView(
		pResource.Get(),
		nullptr,
		&uavDesc,
		descriptor.getCPUHandle()
	);

	UnorderedAccessView UAV(descriptor, this);
	return std::get<UnorderedAccessView>(_viewMap[viewKey] = UAV);
}

auto Texture::getArrayRTV(size_t mipSlice) const -> const RenderTargetView & {
	if (mipSlice >= _resourceDesc.MipLevels || getDepthOrArraySize() <= 1 || !checkRTVSupport())
		return InvalidRTV;

	ViewKey viewKey;
	viewKey.dimension = ViewDimension::VD_ARRAY;
	viewKey.viewType = ViewType::RTV;
	viewKey.mipSlice = mipSlice;
	if (auto iter = _viewMap.find(viewKey); iter != _viewMap.end())
		return std::get<RenderTargetView>(iter->second);

	auto pSharedDevice = getDevice().lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	D3D12_RENDER_TARGET_VIEW_DESC desc;
	desc.Format = _resourceDesc.Format;
	desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
	desc.Texture2DArray.MipSlice = static_cast<UINT>(mipSlice);
	desc.Texture2DArray.FirstArraySlice = 0;
	desc.Texture2DArray.ArraySize = _resourceDesc.DepthOrArraySize;
	desc.Texture2DArray.PlaneSlice = 0;
	pSharedDevice->getD3DDevice()->CreateRenderTargetView(
		_pResource.Get(),
		&desc,
		descriptor.getCPUHandle()
	);

	RenderTargetView RTV(descriptor, this);
	return std::get<RenderTargetView>(_viewMap[viewKey] = RTV);
}

auto Texture::getArrayDSV(size_t mipSlice) const -> const DepthStencilView & {
	if (mipSlice >= _resourceDesc.MipLevels || getDepthOrArraySize() <= 1 || !checkDSVSupport())
		return InvalidDSV;

	ViewKey viewKey;
	viewKey.dimension = ViewDimension::VD_ARRAY;
	viewKey.viewType = ViewType::DSV;
	viewKey.mipSlice = mipSlice;
	if (auto iter = _viewMap.find(viewKey); iter != _viewMap.end())
		return std::get<DepthStencilView>(iter->second);

	auto pSharedDevice = getDevice().lock();
	auto descriptor = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

	D3D12_DEPTH_STENCIL_VIEW_DESC desc;
	desc.Format = _resourceDesc.Format;
	desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DARRAY;
	desc.Flags = D3D12_DSV_FLAG_NONE;
	desc.Texture2DArray.MipSlice = static_cast<UINT>(mipSlice);
	desc.Texture2DArray.FirstArraySlice = 0;
	desc.Texture2DArray.ArraySize = _resourceDesc.DepthOrArraySize;

	pSharedDevice->getD3DDevice()->CreateDepthStencilView(
		_pResource.Get(),
		&desc,
		descriptor.getCPUHandle()
	);

	DepthStencilView DSV(descriptor, this);
	return std::get<DepthStencilView>(_viewMap[viewKey] = DSV);
}

auto Texture::getMipLevels() const -> size_t {
	return _resourceDesc.MipLevels;
}

auto Texture::getDepthOrArraySize() const -> size_t {
	return _resourceDesc.DepthOrArraySize;
}

Texture::~Texture() {
	if (auto pSharedDevice = getDevice().lock()) {
		if (auto *pGlobalResource = pSharedDevice->getGlobalResourceState())
			pGlobalResource->removeGlobalResourceState(_pResource.Get());
	}
}

D3D12_RESOURCE_DESC Texture::make2D(DXGI_FORMAT format, size_t width, size_t height, 
	D3D12_RESOURCE_FLAGS flags, size_t numMipMap)
{
	D3D12_RESOURCE_DESC desc;
	desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	desc.Alignment = 0;
	desc.Width = static_cast<UINT64>(width);
	desc.Height = static_cast<UINT>(height);
	desc.DepthOrArraySize = 1;
	desc.MipLevels = static_cast<UINT16>(numMipMap);
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	desc.Flags = flags;
	return desc;
}

D3D12_RESOURCE_DESC Texture::makeArray(DXGI_FORMAT format, size_t width, size_t height, size_t arraySize,
	D3D12_RESOURCE_FLAGS flags, size_t numMipMap)
{
	D3D12_RESOURCE_DESC desc;
	desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	desc.Alignment = 0;
	desc.Width = static_cast<UINT64>(width);
	desc.Height = static_cast<UINT>(height);
	desc.DepthOrArraySize = static_cast<UINT16>(arraySize);
	desc.MipLevels = static_cast<UINT16>(numMipMap);
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	desc.Flags = flags;
	return desc;
}

D3D12_RESOURCE_DESC Texture::makeCube(DXGI_FORMAT format, size_t width, size_t height, 
	D3D12_RESOURCE_FLAGS flags, size_t numMipMap)
{
	D3D12_RESOURCE_DESC desc;
	desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	desc.Alignment = 0;
	desc.Width = static_cast<UINT64>(width);
	desc.Height = static_cast<UINT>(height);
	desc.DepthOrArraySize = 6;
	desc.MipLevels = static_cast<UINT16>(numMipMap);
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	desc.Flags = flags;
	return desc;
}

bool Texture::checkSRVSupport() const {
	return _isSupportSRV;
}        

bool Texture::checkUAVSupport() const {
	return _isSupportUAV;
}

bool Texture::checkRTVSupport() const {
	return _isSupportRTV;
}

bool Texture::checkDSVSupport() const {
	return _isSupportDSV;
}

bool Texture::checkFormatSupport(D3D12_FORMAT_SUPPORT1 formatSupport1) const {
	return (_formatSupport.Support1 & formatSupport1) != 0;
}

bool Texture::checkFormatSupport(D3D12_FORMAT_SUPPORT2 formatSupport2) const {
	return (_formatSupport.Support2 & formatSupport2) != 0;
}

void Texture::initClearValue(const D3D12_CLEAR_VALUE *pClearValue) {
	if (pClearValue != nullptr) {
		_clearValue = *pClearValue;
	} else {
		_clearValue.Format = _resourceDesc.Format;
		if (_resourceDesc.Flags & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL) {
			_clearValue.DepthStencil.Depth = 1.f;
			_clearValue.DepthStencil.Stencil = 0;
		} else if (_resourceDesc.Flags & D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET) {
			for (auto &c : _clearValue.Color)
				c = 0.f;
		} else {
			std::memset(_clearValue.Color, 0, sizeof(_clearValue.Color));
		}
	}
}

void Texture::initFeatureSupport(ID3D12Device *pDevice, DXGI_FORMAT format) {
	auto getFormatSupport = [&](DXGI_FORMAT fmt) {
		D3D12_FEATURE_DATA_FORMAT_SUPPORT support;
		support.Format = fmt;
		ThrowIfFailed(pDevice->CheckFeatureSupport(
			D3D12_FEATURE_FORMAT_SUPPORT,
			&support,
			sizeof(support)
		));
		return support;
	};
	auto checkRTVSupport = [&](D3D12_FEATURE_DATA_FORMAT_SUPPORT formatSupport) {
		return _resourceDesc.Flags & D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET &&
			   formatSupport.Support1 & D3D12_FORMAT_SUPPORT1_RENDER_TARGET  ;
	};
	auto checkDSVSupport = [&](D3D12_FEATURE_DATA_FORMAT_SUPPORT formatSupport) {
		return _resourceDesc.Flags &D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL &&
			   formatSupport.Support1 & D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL;
	};
	auto checkUASupport = [&](D3D12_FEATURE_DATA_FORMAT_SUPPORT formatSupport) {
		return _resourceDesc.Flags &D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS				&&
			   formatSupport.Support1 & D3D12_FORMAT_SUPPORT1_TYPED_UNORDERED_ACCESS_VIEW	&&
			   formatSupport.Support2 & D3D12_FORMAT_SUPPORT2_UAV_TYPED_LOAD				&&
			   formatSupport.Support2 & D3D12_FORMAT_SUPPORT2_UAV_TYPED_STORE				;
	};
	auto checkSRVSupport = [&](D3D12_FEATURE_DATA_FORMAT_SUPPORT formatSupport) {
		return formatSupport.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE;
	};

	_formatSupport = getFormatSupport(format);
	_isSupportRTV = checkRTVSupport(_formatSupport);
	_isSupportDSV = checkDSVSupport(_formatSupport);
	_isSupportUAV = checkUASupport(_formatSupport);
	_isSupportSRV = checkSRVSupport(_formatSupport);
	if (_resourceDesc.Flags & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL) {
		_isSupportDSV = checkDSVSupport(getFormatSupport(getDepthDSVFormat(format)));
		_isSupportSRV = checkSRVSupport(getFormatSupport(getDepthSRVFormat(format)));
	}
}

}
