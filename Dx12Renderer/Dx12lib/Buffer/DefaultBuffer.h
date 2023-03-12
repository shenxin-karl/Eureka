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
	auto getAddress() const -> D3D12_GPU_VIRTUAL_ADDRESS;
	auto getD3DResource() const -> WRL::ComPtr<ID3D12Resource> override;
	auto getBufferType() const -> BufferType override;
	auto getBufferSize() const -> size_t override;
	void uploadData(ID3D12GraphicsCommandList *pCmdList, const void *pData, size_t sizeInByte);
private:
	std::weak_ptr<Device>		 _pDevice;
	WRL::ComPtr<ID3D12Resource>  _pDefaultResource;
	WRL::ComPtr<ID3D12Resource>  _pUploaderResource;
};

}