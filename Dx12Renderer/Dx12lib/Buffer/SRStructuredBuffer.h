#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Descriptor/DescriptorAllocation.h>
#include <Dx12lib/Resource/IResource.h>

namespace dx12lib {

class SRStructuredBuffer : public ISRStructuredBuffer {
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	size_t getBufferSize() const override;
	size_t getElementCount() const override;
	size_t getElementStride() const override;
	void updateBuffer(const void *pData, size_t sizeInByte, size_t offset = 0) override;
	const ShaderResourceView & getSRV() const override;
	~SRStructuredBuffer() override;
protected:
	SRStructuredBuffer(std::weak_ptr<Device> pDevice, const void *pData, size_t numElements, size_t stride);
private:
	size_t _elementStride;
	ShaderResourceView _srv;
	std::unique_ptr<UploadBuffer> _pUploadBuffer;
};

}
