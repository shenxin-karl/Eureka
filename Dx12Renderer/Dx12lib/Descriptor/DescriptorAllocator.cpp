#include <Dx12lib/Device/Device.h>
#include <Dx12lib/Descriptor/DescriptorAllocator.h>
#include <Dx12lib/Descriptor/DescriptorAllocatorPage.h>
#include <Dx12lib/Descriptor/DescriptorAllocation.h>
#include <Dx12lib/Tool/MakeObejctTool.hpp>

namespace dx12lib {

DescriptorAllocation DescriptorAllocator::allocate(uint32 numDescriptor) {
	assert(numDescriptor <= _numDescriptorPreHeap);
	std::unique_lock lock(_allocationMutex);
	for (auto iter = _availableHeaps.begin(); iter != _availableHeaps.end(); ++iter) {
		auto pPage = _heapPool[*iter];
		DescriptorAllocation alloc = pPage->allocate(numDescriptor);
		if (pPage->getFreeHandle() == 0)
			iter = _availableHeaps.erase(iter);
		if (alloc.isValid())
			return alloc;
	}
	auto pNewPage = createAllocatorPage();
	return pNewPage->allocate(numDescriptor);
}

std::shared_ptr<DescriptorAllocatorPage> DescriptorAllocator::createAllocatorPage() {
	auto pPage = std::make_shared<dx12libTool::MakeDescriptorAllocatorPage>(
		_pDevice,
		_heapType,
		_numDescriptorPreHeap
	);
	_heapPool.push_back(pPage);
	_availableHeaps.insert(_heapPool.size()-1);
	return pPage;
}

DescriptorAllocator::DescriptorAllocator(std::weak_ptr<Device> pDevice, 
	D3D12_DESCRIPTOR_HEAP_TYPE heapType, 
	uint32 numDescriptorPreHeap)
: _numDescriptorPreHeap(numDescriptorPreHeap), _pDevice(pDevice)
, _heapType(heapType) {
}

void DescriptorAllocator::releaseStateDescriptors() {
	std::lock_guard lock(_allocationMutex);
	for (std::size_t i = 0; i < _heapPool.size(); ++i) {
		auto &pPage = _heapPool[i];
		pPage->releaseStaleDescriptors();
		if (pPage->getFreeHandle() > 0)
			_availableHeaps.insert(i);
	}
}

uint32 DescriptorAllocator::getNumDescriptorPerHeap() const noexcept {
	return _numDescriptorPreHeap;
}

void DescriptorAllocator::setNumDescriptorPerHeap(uint32 num) noexcept {
	_numDescriptorPreHeap = num;
}

D3D12_DESCRIPTOR_HEAP_TYPE DescriptorAllocator::getHeapType() const noexcept {
	return _heapType;
}

}
