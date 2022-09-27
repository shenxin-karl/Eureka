#pragma once
#include <Dx12lib/Resource/IResource.h>
#include <Dx12lib/Buffer/DefaultBuffer.h>

namespace dx12lib {

class UAStructuredBuffer : public IUAStructuredBuffer {
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	size_t getBufferSize() const override;
	size_t getElementCount() const override;
	size_t getElementStride() const override;
	const UnorderedAccessView & getUAV() const override;
	const ShaderResourceView & getSRV() const override;
protected:
	UAStructuredBuffer(std::weak_ptr<Device> pDevice, 
		std::shared_ptr<CommandList> pCmdList,
		const void *pData,
		size_t numElements,
		size_t stride
	);
private:
	size_t _elementStride;
	ShaderResourceView _srv;
	UnorderedAccessView _uav;
	std::unique_ptr<DefaultBuffer> _pDefaultBuffer;
};

}
