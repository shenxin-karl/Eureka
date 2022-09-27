#pragma once
#include <span>
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Resource/IResource.h>

namespace dx12lib {

class ReadBackBuffer : public IReadBackBuffer {
public:
	WRL::ComPtr<ID3D12Resource> getD3DResource() const override;
	size_t getBufferSize() const override;
	bool isCompleted() const override;
	const void *getMappedPtr() const override;
	size_t getElementCount() const override;
	size_t getElementStride() const override;
	void setCompletedCallback(const std::function<void(IReadBackBuffer *)> &callback) override;
	~ReadBackBuffer() override;

	template<typename T>
	std::span<const T> visit() const {
		assert(sizeof(T) == _elementStride);
		return std::span<const T>(static_cast<const T *>(getMappedPtr()), getElementCount());
	}
protected:
	friend class CommandList;
	ReadBackBuffer(std::weak_ptr<Device> pDevice, size_t numElements, size_t stride);
	void setCompleted(bool flag);
private:
	bool _isCompleted = false;
	mutable void *_pMapped = nullptr;
	size_t _elementStride;
	std::weak_ptr<Device> _pDevice;
	WRL::ComPtr<ID3D12Resource> _pResource;
	std::function<void(IReadBackBuffer *)> _completedCallBack;
};

}
