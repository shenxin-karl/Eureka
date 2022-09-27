#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Resource/IResource.h>
#include <Dx12lib/Resource/IUnorderedAccessResource.h>

namespace dx12lib {
	
class UnorderedAccess2D : public IUnorderedAccess2D {
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	~UnorderedAccess2D() override;
protected:
	UnorderedAccess2D(std::weak_ptr<Device> pDevice,
		WRL::ComPtr<ID3D12Resource> pResource, 
		D3D12_RESOURCE_STATES state
	);
	UnorderedAccess2D(std::weak_ptr<Device> pDevice,
		size_t width,
		size_t height,
		DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN
	);
private:
	WRL::ComPtr<ID3D12Resource> _pResource;
};

class UnorderedAccess2DArray : public IUnorderedAccess2DArray {
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	~UnorderedAccess2DArray() override;
protected:
	UnorderedAccess2DArray(std::weak_ptr<Device> pDevice,
		WRL::ComPtr<ID3D12Resource> pResource,
		D3D12_RESOURCE_STATES state
	);
	UnorderedAccess2DArray(std::weak_ptr<Device> pDevice,
		size_t width,
		size_t height,
		size_t planeSlice,
		DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN
	);
private:
	WRL::ComPtr<ID3D12Resource> _pResource;
};

class UnorderedAccessCube : public IUnorderedAccessCube {
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	~UnorderedAccessCube() override;
protected:
	UnorderedAccessCube(std::weak_ptr<Device> pDevice,
		WRL::ComPtr<ID3D12Resource> pResource,
		D3D12_RESOURCE_STATES state
	);
	UnorderedAccessCube(std::weak_ptr<Device> pDevice,
		size_t width,
		size_t height,
		size_t mipLevels = 1,
		DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN
	);
private:
	WRL::ComPtr<ID3D12Resource> _pResource;
};

}
