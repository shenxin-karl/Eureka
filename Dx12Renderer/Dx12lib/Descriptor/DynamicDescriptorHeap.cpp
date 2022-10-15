#include <iostream>
#include <Dx12lib/Pipeline/RootSignature.h>
#include <Dx12lib/Descriptor/DynamicDescriptorHeap.h>
#include <Dx12lib/Device/Device.h>
#include <Dx12lib/Context/CommandList.h>

namespace dx12lib {

DynamicDescriptorHeap::DynamicDescriptorHeap(std::weak_ptr<Device> pDevice, 
	D3D12_DESCRIPTOR_HEAP_TYPE heapType, 
	size_t numDescriptorsPerHeap)
: _numDescriptorsPerHeap(numDescriptorsPerHeap), _heapType(heapType), _pDevice(pDevice)
{
	_pD3DDevice = pDevice.lock()->getD3DDevice();
	_descriptorHandleIncrementSize = pDevice.lock()->getD3DDevice()->GetDescriptorHandleIncrementSize(heapType);
	reset();
}

void DynamicDescriptorHeap::parseRootSignature(std::shared_ptr<RootSignature> pRootSignature) {
	assert(pRootSignature != nullptr);
	_pRootSignature = pRootSignature;

	size_t currentOffset = 0;
	const auto &descriptorPerTable = pRootSignature->getDescriptorPerTableByType(_heapType);
	const auto descriptorTableBitMask = pRootSignature->getDescriptorTableBitMask(_heapType);
	_descriptorTableBitMask = descriptorTableBitMask;
	_staleDescriptorTableBitMask = descriptorTableBitMask;

	for (std::size_t i = 0; i < kMaxDescriptorTables; ++i) {
		if (!descriptorTableBitMask.test(i))
			continue;

		size_t numDescriptors = descriptorPerTable[i];
		DescriptorTableCache &descriptorTableCache = _descriptorTableCache[i];
		descriptorTableCache._numDescriptors = numDescriptors;
		descriptorTableCache._pBaseHandle = _descriptorHandleCache.data() + currentOffset;
		currentOffset += numDescriptors;
	}

	/// out of cache range
	assert(currentOffset < kMaxDescriptorTables);
	_skipSubmit = _descriptorTableBitMask.count() > 0;
}

void DynamicDescriptorHeap::commitStagedDescriptorForDraw(CommandList *pCmdList) {
	commitDescriptorTables(pCmdList, &ID3D12GraphicsCommandList::SetGraphicsRootDescriptorTable);
}

void DynamicDescriptorHeap::commitStagedDescriptorForDispatch(CommandList *pCmdList) {
	commitDescriptorTables(pCmdList, &ID3D12GraphicsCommandList::SetComputeRootDescriptorTable);
}

void DynamicDescriptorHeap::reset() {
	_numFreeHandles = 0;
	_pCurrentDescriptorHeap = nullptr;
	_currentCPUDescriptorHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(D3D12_DEFAULT);
	_currentGPUDescriptorHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(D3D12_DEFAULT);
	_pRootSignature = nullptr;
	_descriptorTableBitMask.reset();
	_staleDescriptorTableBitMask.reset();
	_availableDescriptorHeaps = _descriptorHeapPool;
	for (std::size_t i = 0; i < kMaxDescriptorTables; ++i) {
		_descriptorTableCache[i].reset();
		_descriptorHandleCache[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(D3D12_DEFAULT);
	}
}

void DynamicDescriptorHeap::stageDescriptor(const ShaderRegister &sr, const D3D12_CPU_DESCRIPTOR_HANDLE &descriptor) {
	assert(_pRootSignature != nullptr);
	auto location = _pRootSignature->getShaderParamLocation(sr);
	if (location.has_value()) {
		stageDescriptors(
			location->rootParamIndex, 
			location->offset, 
			1, 
			descriptor
		);
	} else {
		assert(false);
		std::cerr << "The current register does not: "
				  << "slot: "
		          << static_cast<size_t>(sr.slot)
				  << ", space:" << static_cast<size_t>(sr.space)
				  << std::endl;
	}
}

void DynamicDescriptorHeap::stageDescriptors(size_t rootParameterIndex,
                                             size_t offset,
                                             size_t numDescripotrs,
                                             const D3D12_CPU_DESCRIPTOR_HANDLE &srcDescriptor)
{
	if (numDescripotrs > _numDescriptorsPerHeap || rootParameterIndex >= kMaxDescriptorTables)
		throw std::bad_alloc();

	auto &descriptorTableCache = _descriptorTableCache[rootParameterIndex];
	if ((offset + numDescripotrs) > descriptorTableCache._numDescriptors) {
		std::stringstream sbuf;
		sbuf << "Number of descriptors exceeds the number of descriptors in the descriptor table." << std::endl;
		sbuf << "rootParameterIndex: " << rootParameterIndex << std::endl
			<< "offset: " << offset << std::endl
			<< "numDescriptors: " << numDescripotrs << std::endl
			<< "descriptorTableCache._numDescriptors: " << descriptorTableCache._numDescriptors << std::endl;
		throw std::length_error(sbuf.str());
	}

	D3D12_CPU_DESCRIPTOR_HANDLE *pDstDescriptor = (descriptorTableCache._pBaseHandle + offset);
	bool dirty = false;
	for (size_t i = 0; i < numDescripotrs; ++i) {
		auto descriptor = CD3DX12_CPU_DESCRIPTOR_HANDLE(
			srcDescriptor, 
			static_cast<INT>(i), 
			static_cast<UINT>(_descriptorHandleIncrementSize)
		);
		if (descriptor.ptr != pDstDescriptor[i].ptr) {
			pDstDescriptor[i] = descriptor;
			dirty = true;
		}
	}
	if (dirty)
		_staleDescriptorTableBitMask.set(rootParameterIndex, true);
}

auto DynamicDescriptorHeap::getDescriptorHandleIncrementSize() const -> std::size_t {
	return _descriptorHandleIncrementSize;
}

size_t DynamicDescriptorHeap::computeStaleDescriptorCount() const {
	if (_staleDescriptorTableBitMask.none())
		return 0;

	size_t numStaleDescriptors = 0;
	for (std::size_t i = 0; i < kMaxDescriptorTables; ++i) {
		int flag = _staleDescriptorTableBitMask.test(i);
		numStaleDescriptors += flag * _descriptorTableCache[i]._numDescriptors;
	}
	return numStaleDescriptors;
}

void DynamicDescriptorHeap::commitDescriptorTables(CommandList *pCmdList, const CommitFunc &setFunc) {
	if (!_skipSubmit)
		return;

	size_t numDescriptors = computeStaleDescriptorCount();
	if (numDescriptors == 0)
		return;

	auto *pD3DCommandList = pCmdList->getD3DCommandList();
	if (_pCurrentDescriptorHeap == nullptr || _numFreeHandles < numDescriptors) {
		_staleDescriptorTableBitMask = _descriptorTableBitMask;
		_pCurrentDescriptorHeap = requestDescriptorHeap();
		_currentCPUDescriptorHandle = _pCurrentDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		_currentGPUDescriptorHandle = _pCurrentDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
		_numFreeHandles = _numDescriptorsPerHeap;
		pCmdList->setDescriptorHeap(_heapType, _pCurrentDescriptorHeap.Get());
	}

	for (std::size_t rootIndex = 0; rootIndex < kMaxDescriptorTables; ++rootIndex) {
		if (!_staleDescriptorTableBitMask.test(rootIndex))
			continue;

		UINT numDescriptors = static_cast<UINT>(_descriptorTableCache[rootIndex]._numDescriptors);
		auto *pSrcHandle = _descriptorTableCache[rootIndex]._pBaseHandle;
		D3D12_CPU_DESCRIPTOR_HANDLE pDstDescriptorRangeStarts[] = { _currentCPUDescriptorHandle };
		UINT pDstDescriptorRangeSizes[] = { numDescriptors };

		// todo-note: 如果 CopyDescriptors 出现错误, 检查 _pBaseHandle 的值是否有效. 确认是不是 stageDescriptors 时没有设置 offset
		_pD3DDevice->CopyDescriptors(
			1, pDstDescriptorRangeStarts, pDstDescriptorRangeSizes, 
			numDescriptors, pSrcHandle, nullptr,
			_heapType
		);

		// Bind to the Command list 
		_numFreeHandles -= numDescriptors;
		(pD3DCommandList->*setFunc)(static_cast<UINT>(rootIndex), _currentGPUDescriptorHandle);
		_currentCPUDescriptorHandle.Offset(static_cast<INT>(numDescriptors), static_cast<UINT>(_descriptorHandleIncrementSize));
		_currentGPUDescriptorHandle.Offset(static_cast<INT>(numDescriptors), static_cast<UINT>(_descriptorHandleIncrementSize));
	}
	_staleDescriptorTableBitMask.reset();
}

WRL::ComPtr<ID3D12DescriptorHeap> DynamicDescriptorHeap::requestDescriptorHeap() {
	WRL::ComPtr<ID3D12DescriptorHeap> pDescriptorHeap;
	if (!_availableDescriptorHeaps.empty()) {
		pDescriptorHeap = _availableDescriptorHeaps.front();
		_availableDescriptorHeaps.pop();
	} else {
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		heapDesc.NodeMask = 0;
		heapDesc.NumDescriptors = static_cast<UINT>(_numDescriptorsPerHeap);
		heapDesc.Type = _heapType;
		ThrowIfFailed(_pDevice.lock()->getD3DDevice()->CreateDescriptorHeap(
			&heapDesc,
			IID_PPV_ARGS(&pDescriptorHeap)
		));
		_descriptorHeapPool.push(pDescriptorHeap);
	}
	return pDescriptorHeap;
}

DynamicDescriptorHeap::DescriptorTableCache::DescriptorTableCache() {
	reset();
}

void DynamicDescriptorHeap::DescriptorTableCache::reset() {
	_numDescriptors = 0;
	_pBaseHandle = nullptr;
}

}