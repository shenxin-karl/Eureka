#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Buffer/CBufferVisitor.hpp>
#include <Dx12lib/Descriptor/DescriptorAllocation.h>
#include <Dx12lib/Resource/IResource.h>

namespace dx12lib {

class UploadBuffer;

class ConstantBuffer : public IConstantBuffer {
protected:
	ConstantBuffer(std::weak_ptr<Device> pDevice, const void *pData, std::size_t sizeInByte);
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	size_t getBufferSize() const override;
	size_t getElementStride() const override;
	BYTE *getMappedPtr() override;
	const BYTE *getMappedPtr() const override;
	void updateBuffer(const void *pData, size_t sizeInByte, size_t offset = 0) override;
	const ConstantBufferView & getCBV() const override;

	template<typename T>
	CBufferVisitor<T> visit() {
		assert(sizeof(T) <= getElementStride());
		return CBufferVisitor<T>(reinterpret_cast<T *>(getMappedPtr()));
	}

	template<typename T>
	CBufferVisitor<const T> visit() const {
		assert(sizeof(T) <= getElementStride());
		return CBufferVisitor<T>(getMappedPtr());
	}
private:
	ConstantBufferView _constantBufferView;
	std::unique_ptr<UploadBuffer> _pUploadBuffer;
};

}
