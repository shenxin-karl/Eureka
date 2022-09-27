#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Resource/IResource.h>
#include <Dx12lib/Descriptor/DescriptorAllocation.h>
#include <Dx12lib/Resource/ITextureResource.h>

namespace dx12lib {

class SamplerTexture2D : public ITextureResource2D {
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	~SamplerTexture2D() override;
protected:
	SamplerTexture2D(std::weak_ptr<Device> pDevice,
		WRL::ComPtr<ID3D12Resource> pResource,
		D3D12_RESOURCE_STATES state
	);
private:
	WRL::ComPtr<ID3D12Resource> _pResource;
};

class SamplerTexture2DArray : public ITextureResource2DArray {
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	~SamplerTexture2DArray() override;
protected:
	SamplerTexture2DArray(std::weak_ptr<Device> pDevice,
		WRL::ComPtr<ID3D12Resource> pResource,
		D3D12_RESOURCE_STATES state
	);
private:
	WRL::ComPtr<ID3D12Resource> _pResource;
};

class SamplerTextureCube : public ITextureResourceCube {
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	~SamplerTextureCube() override;
protected:
	SamplerTextureCube(std::weak_ptr<Device> pDevice,
		WRL::ComPtr<ID3D12Resource> pResource,
		D3D12_RESOURCE_STATES state
	);
private:
	WRL::ComPtr<ID3D12Resource> _pResource;
};

}
