#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Resource/IResource.h>

namespace dx12lib {

class DefaultBuffer : public IBufferResource {
public:
	DefaultBuffer(std::weak_ptr<Device> pDevice, 
		ID3D12GraphicsCommandList *pCmdList, 
		const void *pData, 
		size_t sizeInByte,
		D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE,
		D3D12_RESOURCE_STATES finalState = D3D12_RESOURCE_STATE_GENERIC_READ
	);
	~DefaultBuffer() override;
	D3D12_GPU_VIRTUAL_ADDRESS getAddress() const;
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	BufferType getBufferType() const override;
	size_t getBufferSize() const override;
private:
	std::weak_ptr<Device> _pDevice;
	WRL::ComPtr<ID3D12Resource>  _pDefaultResource;
	WRL::ComPtr<ID3D12Resource>  _pUploaderResource;
};

}