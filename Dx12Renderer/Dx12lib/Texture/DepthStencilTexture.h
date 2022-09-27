#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Resource/IResource.h>
#include <Dx12lib/Descriptor/DescriptorAllocation.h>
#include <Dx12lib/Resource/IDepthStencilResource.h>

namespace dx12lib {

class DepthStencil2D : public IDepthStencil2D {
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	~DepthStencil2D() override;
protected:
	DepthStencil2D(std::weak_ptr<Device> pDevice, 
		size_t width, 
		size_t height,
		const D3D12_CLEAR_VALUE *pClearValue = nullptr
	);
private:
	WRL::ComPtr<ID3D12Resource> _pResource;
};

class DepthStencil2DArray : public IDepthStencil2DArray {
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	~DepthStencil2DArray() override;
protected:
	DepthStencil2DArray(std::weak_ptr<Device> pDevice,
		size_t width,
		size_t height,
		size_t planeSize,
		const D3D12_CLEAR_VALUE *pClearValue = nullptr
	);
private:
	WRL::ComPtr<ID3D12Resource> _pResource;
};

}
