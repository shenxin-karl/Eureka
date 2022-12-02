#pragma once
#include "Dx12lib/dx12libStd.h"

namespace dx12lib {

class DynamicDescriptorHeap {
public:
	DynamicDescriptorHeap(std::weak_ptr<Device> pDevice, 
		D3D12_DESCRIPTOR_HEAP_TYPE heapType, 
		size_t numDescriptorsPerHeap
	);
	void parseRootSignature(std::shared_ptr<RootSignature> pRootSignature);
	void commitStagedDescriptorForDraw(CommandList *pCmdList);
	void commitStagedDescriptorForDispatch(CommandList *pCmdList);
	void reset();
	void stageDescriptor(const ShaderRegister &sr, const D3D12_CPU_DESCRIPTOR_HANDLE &descriptor);
	void stageDescriptors(size_t rootParameterIndex,
		size_t offset,
		size_t numDescriptors,
		const D3D12_CPU_DESCRIPTOR_HANDLE &srcDescriptor
	);
	auto getDescriptorHandleIncrementSize() const -> std::size_t;
private:
	size_t computeStaleDescriptorCount() const;

	using CommitFunc = decltype(&ID3D12GraphicsCommandList::SetGraphicsRootDescriptorTable);
	void commitDescriptorTables(CommandList *pCmdList, const CommitFunc &setFunc);

	WRL::ComPtr<ID3D12DescriptorHeap> requestDescriptorHeap();

	using DescriptorHeapPool = std::queue<WRL::ComPtr<ID3D12DescriptorHeap>>;
	struct DescriptorTableCache {
		DescriptorTableCache();
		void reset();
	public:
		size_t                       _numDescriptors;
		D3D12_CPU_DESCRIPTOR_HANDLE *_pBaseHandle;
	};

	using DescriptorHandleCache = std::array<D3D12_CPU_DESCRIPTOR_HANDLE, kMaxDescriptor>;
private:
	size_t                            _numDescriptorsPerHeap;
	size_t                            _descriptorHandleIncrementSize;
	D3D12_DESCRIPTOR_HEAP_TYPE        _heapType;
	DescriptorTableCache              _descriptorTableCache[kMaxRootParameter];
	std::weak_ptr<Device>             _pDevice;
	ID3D12Device					 *_pD3DDevice;
	bool							  _skipSubmit = false;
	std::bitset<kMaxRootParameter>	  _descriptorTableBitMask;
	std::bitset<kMaxRootParameter>	  _staleDescriptorTableBitMask;
	DescriptorHandleCache             _descriptorHandleCache;


	DescriptorHeapPool                _descriptorHeapPool;
	DescriptorHeapPool                _availableDescriptorHeaps;

	size_t                            _numFreeHandles;
	CD3DX12_CPU_DESCRIPTOR_HANDLE     _currentCPUDescriptorHandle;
	CD3DX12_GPU_DESCRIPTOR_HANDLE     _currentGPUDescriptorHandle;
	WRL::ComPtr<ID3D12DescriptorHeap> _pCurrentDescriptorHeap;

	std::shared_ptr<RootSignature>	  _pRootSignature;
};

}