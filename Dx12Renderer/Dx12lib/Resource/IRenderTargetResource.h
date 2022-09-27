#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Resource/ResourceView.hpp>
#include <Dx12lib/Resource/IResource.h>
#include <Dx12lib/Resource/ITextureResource.h>

namespace dx12lib {

interface IRenderTarget : virtual IResource {
	IRenderTarget();
	D3D12_CLEAR_VALUE getClearValue() const;
protected:
	D3D12_CLEAR_VALUE _clearValue;
};

interface IRenderTarget2D : IRenderTarget, ITextureResource2D {
	const RenderTargetView &getRTV(size_t mipSlice = 0) const;
private:
	mutable ViewManager<RenderTargetView> _rtvMgr;
};

interface IRenderTarget2DArray : IRenderTarget, ITextureResource2DArray {
	const RenderTargetView &getPlaneRTV(size_t planeSlice, size_t mipSlice = 0) const;
private:
	mutable std::map<size_t, ViewManager<RenderTargetView>> _planeRtvMgr;
};

interface IRenderTargetCube : IRenderTarget, ITextureResourceCube {
	const RenderTargetView &getFaceRTV(CubeFace face, size_t mipSlice = 0) const;
private:
	mutable std::map<CubeFace, ViewManager<RenderTargetView>> _cubeRtvMgr;
};
	
}
