#pragma once
#include <Dx12lib/dx12libStd.h>
#include <memory>

namespace dx12lib {

class DescriptorAllocatorPage;

class DescriptorAllocation {
public:
	DescriptorAllocation();
	DescriptorAllocation(const DescriptorAllocation &other);
	DescriptorAllocation(DescriptorAllocation &&other) noexcept;
	DescriptorAllocation &operator=(const DescriptorAllocation &other);
	DescriptorAllocation &operator=(DescriptorAllocation &&other) noexcept;
	~DescriptorAllocation();
	friend void swap(DescriptorAllocation &lhs, DescriptorAllocation &rhs) noexcept;
protected:
	DescriptorAllocation(D3D12_CPU_DESCRIPTOR_HANDLE handle,
		std::atomic_size_t *pRefCount,
		size_t numHandle,
		size_t handleSize,
		std::shared_ptr<DescriptorAllocatorPage> pPage
	);
public:
	size_t getNumHandle() const noexcept;
	size_t getHandleSize() const noexcept;
	D3D12_CPU_DESCRIPTOR_HANDLE getCPUHandle(size_t offset = 0) const;
	bool isNull() const noexcept;
	bool isValid() const noexcept;
	void free();
private:
	friend class DescriptorAllocatorPage;
	void reset() noexcept;
private:
	size_t  _numHandle;
	size_t  _handleSize;
	std::atomic_size_t *_pRefCount;
	D3D12_CPU_DESCRIPTOR_HANDLE _baseHandle; 
	std::shared_ptr<DescriptorAllocatorPage> _pPage; 
};

}