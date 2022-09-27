#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Descriptor/DescriptorAllocation.h>

namespace dx12lib {

class DescriptorAllocatorPage : public std::enable_shared_from_this<DescriptorAllocatorPage> {
public:
	DescriptorAllocatorPage();
	DescriptorAllocatorPage(const DescriptorAllocatorPage &) = delete;
	DescriptorAllocatorPage(DescriptorAllocatorPage &&other) noexcept;
	DescriptorAllocatorPage &operator=(const DescriptorAllocatorPage &) = delete;
	DescriptorAllocatorPage &operator=(DescriptorAllocatorPage &&other) noexcept;
	friend void swap(DescriptorAllocatorPage &lhs, DescriptorAllocatorPage &rhs) noexcept;
protected:
	DescriptorAllocatorPage(std::weak_ptr<Device> pDevice, 
		D3D12_DESCRIPTOR_HEAP_TYPE heapType, 
		size_t numDescriptorPreHeap
	);
public:
	D3D12_DESCRIPTOR_HEAP_TYPE getHeapType() const;
	DescriptorAllocation allocate(size_t numDescriptor);
	size_t getFreeHandle() const;
	bool hasSpace(size_t numDescriptor) const;
	void free(DescriptorAllocation &&allocation);
	void releaseStaleDescriptors();
private:
	size_t computeOffset(D3D12_CPU_DESCRIPTOR_HANDLE handle) const;
	void addNewBlock(std::size_t offset, std::size_t numDescriptor);
	void freeBlock(std::size_t offset, std::size_t numDescriptor);
private:
	friend class Device;
	friend class DescriptorAllocator;
	struct FreeBlockInfo;
	using OffsetType = std::size_t;
	using SizeType = std::size_t;
	using FreeListByOffset = std::map<OffsetType, FreeBlockInfo>;
	using FreeListBySize = std::multimap<SizeType, FreeListByOffset::iterator>;
	struct FreeBlockInfo {
		std::size_t  size;
		FreeListBySize::iterator sizeIter;
	};

	struct StaleDescriptorInfo {
		size_t offset;
		size_t size;
	};
private:
	size_t                            _numFreeHandle;
	size_t                            _numDescriptorInHeap;
	size_t                            _descriptorHandleIncrementSize;
	CD3DX12_CPU_DESCRIPTOR_HANDLE     _baseDescriptor;
	mutable std::mutex                _allocationMutex;
	std::weak_ptr<Device>             _pDevice;
	D3D12_DESCRIPTOR_HEAP_TYPE        _heapType;
	std::queue<StaleDescriptorInfo>   _staleAllocation;
	WRL::ComPtr<ID3D12DescriptorHeap> _pDescriptorHeap;
	// std::vector<std::atomic_size_t>   _descriptorAllocationRefCount;	 
	FreeListBySize                    _freeListBySize;
	FreeListByOffset                  _freeListByOffset;
	std::unique_ptr<std::atomic_size_t[]> _pDescriptorAllocationRefCount;
};

}