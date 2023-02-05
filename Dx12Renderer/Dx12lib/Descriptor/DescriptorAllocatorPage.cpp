#include <Dx12lib/Descriptor/DescriptorAllocatorPage.h>
#include <Dx12lib/Device/Device.h>

namespace dx12lib {

DescriptorAllocatorPage::DescriptorAllocatorPage() 
: _numFreeHandle(0), _numDescriptorInHeap(0), _descriptorHandleIncrementSize(0)
, _baseDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE{ 0 }), _heapType(D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES) {
}

DescriptorAllocatorPage::DescriptorAllocatorPage(DescriptorAllocatorPage &&other) noexcept 
: DescriptorAllocatorPage() 
{
	swap(*this, other);
}

DescriptorAllocatorPage::DescriptorAllocatorPage(std::weak_ptr<Device> pDevice, 
	D3D12_DESCRIPTOR_HEAP_TYPE heapType, 
	size_t numDescriptorPreHeap)
: _pDevice(pDevice), _heapType(heapType)
, _pDescriptorAllocationRefCount(new std::atomic_size_t[numDescriptorPreHeap] {0})
{
	ID3D12Device *pD3DDevice = pDevice.lock()->getD3DDevice();
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = static_cast<UINT>(numDescriptorPreHeap);
	heapDesc.Type = _heapType;
	ThrowIfFailed(pD3DDevice->CreateDescriptorHeap(
		&heapDesc,
		IID_PPV_ARGS(&_pDescriptorHeap)
	));

	_numFreeHandle = numDescriptorPreHeap;
	_numDescriptorInHeap = numDescriptorPreHeap;
	_descriptorHandleIncrementSize = pD3DDevice->GetDescriptorHandleIncrementSize(_heapType);
	_baseDescriptor = _pDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	addNewBlock(0, numDescriptorPreHeap);
}

D3D12_DESCRIPTOR_HEAP_TYPE DescriptorAllocatorPage::getHeapType() const {
	return _heapType;
}

size_t DescriptorAllocatorPage::getFreeHandle() const {
	return _numFreeHandle;
}

bool DescriptorAllocatorPage::hasSpace(size_t numDescriptor) const {
	return numDescriptor <= _numFreeHandle;
}

DescriptorAllocation DescriptorAllocatorPage::allocate(size_t numDescriptor) {
	std::lock_guard lock(_allocationMutex);
	if (numDescriptor > _numFreeHandle)
		return {};

	// A block of the appropriate size was found 
	auto iter = _freeListBySize.lower_bound(numDescriptor);
	if (iter == _freeListBySize.end())
		return {};

	auto [size, offsetIt] = *iter;
	UINT offset = static_cast<INT>(offsetIt->first);
	auto descriptor = _baseDescriptor;
	descriptor.Offset(offset, static_cast<UINT>(_descriptorHandleIncrementSize));
	assert(offset < _numDescriptorInHeap);
	_pDescriptorAllocationRefCount[offset].store(1);
	DescriptorAllocation ret = {
		static_cast<D3D12_CPU_DESCRIPTOR_HANDLE>(descriptor),
		&_pDescriptorAllocationRefCount[offset],
		numDescriptor,
		_descriptorHandleIncrementSize,
		shared_from_this(),
	};
	
	_freeListByOffset.erase(offset);
	_freeListBySize.erase(iter);
	size_t newSize = static_cast<UINT>(size) - numDescriptor;
	size_t newOffset = offset + numDescriptor;
	_numFreeHandle -= numDescriptor;
	if (newSize > 0)
		addNewBlock(newOffset, newSize);

	return ret;
}


void DescriptorAllocatorPage::free(DescriptorAllocation &&allocation) {
	auto temp = std::move(allocation);
	assert(*temp._pRefCount == 0);
	StaleDescriptorInfo staleInfo = {
		computeOffset(temp.getCPUHandle()),
		temp.getNumHandle(),
	};
	temp.reset();
	std::lock_guard lock(_allocationMutex);
	_staleAllocation.push(staleInfo);
}

void DescriptorAllocatorPage::releaseStaleDescriptors() {
	while (!_staleAllocation.empty()) {
		auto staleInfo = _staleAllocation.front();
		_staleAllocation.pop();
		freeBlock(staleInfo.offset, staleInfo.size);
	}
}

size_t DescriptorAllocatorPage::computeOffset(D3D12_CPU_DESCRIPTOR_HANDLE handle) const {
	auto offset = (handle.ptr - _baseDescriptor.ptr) / _descriptorHandleIncrementSize;
	return static_cast<size_t>(offset);
}

void DescriptorAllocatorPage::addNewBlock(std::size_t offset, std::size_t numDescriptor) {
	auto [offsetIt, flag] = _freeListByOffset.emplace(offset, FreeBlockInfo{ numDescriptor });
	auto sizeIt = _freeListBySize.emplace(numDescriptor, offsetIt);
	offsetIt->second.sizeIter = sizeIt;
	assert(flag);
}

void DescriptorAllocatorPage::freeBlock(std::size_t offset, std::size_t numDescriptor) {
	auto nextOffsetIt = _freeListByOffset.lower_bound(offset);
	auto newOffset = offset;
	auto newSize = numDescriptor;

	//        prev             current               next
	// |----------------|------------------|--------------------|

	// try merge previous block
	if (nextOffsetIt != _freeListByOffset.begin()) {
		auto prevOffsetIt = nextOffsetIt;
		--prevOffsetIt;
		if (prevOffsetIt->first + prevOffsetIt->second.size == offset) {	// Is a continuous block  
			newOffset = prevOffsetIt->first;
			newSize += prevOffsetIt->second.size;
			_freeListBySize.erase(prevOffsetIt->second.sizeIter);
			_freeListByOffset.erase(prevOffsetIt);
		}
	}

	// try merge next block
	if (nextOffsetIt != _freeListByOffset.end()) {
		if ((offset + numDescriptor == nextOffsetIt->first)) {			// Is a continuous block  
			newSize += nextOffsetIt->second.size;
			_freeListBySize.erase(nextOffsetIt->second.sizeIter);
			_freeListByOffset.erase(nextOffsetIt);
		}
	}

	addNewBlock(newOffset, newSize);
}

DescriptorAllocatorPage &DescriptorAllocatorPage::operator=(DescriptorAllocatorPage &&other) noexcept {
	DescriptorAllocatorPage tmp;
	swap(*this, tmp);
	swap(*this, other);
	return *this;
}

void swap(DescriptorAllocatorPage &lhs, DescriptorAllocatorPage &rhs) noexcept {
	using std::swap;
	swap(lhs._numFreeHandle, rhs._numFreeHandle);
	swap(lhs._numDescriptorInHeap, rhs._numDescriptorInHeap);
	swap(lhs._descriptorHandleIncrementSize, rhs._descriptorHandleIncrementSize);
	swap(lhs._pDescriptorAllocationRefCount, rhs._pDescriptorAllocationRefCount);
	swap(lhs._pDevice, rhs._pDevice);
	swap(lhs._heapType, rhs._heapType);
	swap(lhs._staleAllocation, rhs._staleAllocation);
	swap(lhs._pDescriptorHeap, rhs._pDescriptorHeap);
}

}