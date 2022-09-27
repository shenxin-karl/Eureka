#pragma once
#include <Dx12lib/Resource/IResource.h>
#include <Dx12lib/Resource/IRenderTargetResource.h>

namespace dx12lib {

class RenderTarget2D : public IRenderTarget2D {
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	~RenderTarget2D() override;
protected:
	RenderTarget2D(std::weak_ptr<Device> pDevice, 
		WRL::ComPtr<ID3D12Resource> pResource, 
		D3D12_RESOURCE_STATES state,
		const D3D12_CLEAR_VALUE *pClearValue = nullptr
	);
	RenderTarget2D(std::weak_ptr<Device> pDevice,
		size_t width, 
		size_t height,
		const D3D12_CLEAR_VALUE *pClearValue = nullptr
	);
private:
	WRL::ComPtr<ID3D12Resource> _pResource;
};

class RenderTarget2DArray : public IRenderTarget2DArray {
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	~RenderTarget2DArray() override;
protected:
	RenderTarget2DArray(std::weak_ptr<Device> pDevice,
		WRL::ComPtr<ID3D12Resource> pResource,
		D3D12_RESOURCE_STATES state
	);
	RenderTarget2DArray(std::weak_ptr<Device> pDevice,
		size_t width,
		size_t height,
		size_t planeSlice,
		const D3D12_CLEAR_VALUE *pClearValue = nullptr
	);
private:
	WRL::ComPtr<ID3D12Resource> _pResource;
};

class RenderTargetCube : public IRenderTargetCube {
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	~RenderTargetCube() override;
protected:
	RenderTargetCube(std::weak_ptr<Device> pDevice,
		WRL::ComPtr<ID3D12Resource> pResource,
		D3D12_RESOURCE_STATES state
	);
	RenderTargetCube(std::weak_ptr<Device> pDevice,
		size_t width,
		size_t height,
		D3D12_CLEAR_VALUE *pClearValue = nullptr
	);
private:
	WRL::ComPtr<ID3D12Resource> _pResource;
};


}
