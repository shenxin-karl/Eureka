#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Resource/IResource.h>
#include <Dx12lib/Resource/ITextureResource.h>

namespace dx12lib {

interface IUnorderedAccess : virtual IResource {
	using IResource::IResource;
};

interface IUnorderedAccess2D : IUnorderedAccess, ITextureResource2D {
	const UnorderedAccessView &getUAV(size_t mipSlice = 0) const;
private:
	mutable ViewManager<UnorderedAccessView> _uavMgr;
};

interface IUnorderedAccess2DArray : IUnorderedAccess, ITextureResource2DArray {
	const UnorderedAccessView &getPlaneUAV(size_t planeSlice, size_t mipSlice = 0) const;
private:
	mutable std::map<size_t, ViewManager<UnorderedAccessView>> _planeUavMgr;
};

interface IUnorderedAccessCube : IUnorderedAccess, ITextureResourceCube {
	const UnorderedAccessView &getFaceUAV(CubeFace face, size_t mipSlice = 0) const;
	const UnorderedAccessView &get2DArrayUAV(size_t mipSlice = 0) const;
private:
	mutable ViewManager<UnorderedAccessView> _2DArrayUavMgr;
	mutable std::map<CubeFace, ViewManager<UnorderedAccessView>> _cubeUavMgr;
};

}
