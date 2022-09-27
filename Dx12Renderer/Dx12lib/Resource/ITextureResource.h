#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Resource/ResourceView.hpp>
#include <Dx12lib/Resource/IResource.h>

namespace dx12lib {

struct ITextureResource : virtual IResource {
	using IResource::IResource;
	size_t getMipLevels() const;
	virtual ShaderResourceDimension getDimension() const = 0;
	virtual const ShaderResourceView &getSRV(size_t mipSlice = 0) const = 0;
};

struct ITextureResource2D : ITextureResource {
	using ITextureResource::ITextureResource;
	ShaderResourceDimension getDimension() const final;
	const ShaderResourceView &getSRV(size_t mipSlice = 0) const override;
protected:
	mutable ViewManager<ShaderResourceView> _srvMgr;
};

struct ITextureResource2DArray : ITextureResource {
	using ITextureResource::ITextureResource;
	ShaderResourceDimension getDimension() const final;
	size_t getPlaneSlice() const;
	const ShaderResourceView &getSRV(size_t mipSlice = 0) const override;
	virtual const ShaderResourceView &getPlaneSRV(size_t planeSlice, size_t mipSlice = 0) const;
protected:
	mutable ViewManager<ShaderResourceView> _srvMgr;
	mutable std::map<size_t, ViewManager<ShaderResourceView>> _planeSrvMgr;
};

struct ITextureResourceCube : ITextureResource {
	using ITextureResource::ITextureResource;
	ShaderResourceDimension getDimension() const final;
	const ShaderResourceView &getSRV(size_t mipSlice = 0) const override;
	const ShaderResourceView &getFaceSRV(CubeFace face, size_t mipSlice = 0) const;
protected:
	mutable ViewManager<ShaderResourceView> _srvMgr;
	mutable std::map<CubeFace, ViewManager<ShaderResourceView>> _cubeSrvMgr;
};

bool hasAlpha(DXGI_FORMAT format);
bool isUAVCompatibleFormat(DXGI_FORMAT format);
bool isSRGBFormat(DXGI_FORMAT format);
bool isBGRFormat(DXGI_FORMAT format);
bool isDepthFormat(DXGI_FORMAT format);
bool hasStencilFormat(DXGI_FORMAT format);
DXGI_FORMAT getDepthDSVFormat(DXGI_FORMAT format);
DXGI_FORMAT getDepthSRVFormat(DXGI_FORMAT format);
DXGI_FORMAT getSRGBFormat(DXGI_FORMAT format, bool hasStencil);
DXGI_FORMAT getUAVCompatableFormat(DXGI_FORMAT format);
DXGI_FORMAT getTypelessFormat(DXGI_FORMAT format);

}

