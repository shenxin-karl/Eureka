#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Context/ContextProxy.hpp>
#include <Dx12lib/Context/FrameResourceQueue.h>

namespace dx12lib {

class CommandQueue {
protected:
	CommandQueue(std::weak_ptr<Device> pDevice, D3D12_COMMAND_LIST_TYPE queueType);
public:
	CommandQueue(const CommandQueue &) = delete;
	ID3D12CommandQueue *getD3D12CommandQueue() const;
	uint64 signal(std::shared_ptr<SwapChain> pSwapChain);
	void delayExecuted(ContextProxy pContext);
	void executeCommandList(ContextProxy pContext);
	void executeCommandList(std::vector<ContextProxy> contextList);
	bool isFenceComplete(uint64 fenceValue) const noexcept;
	void waitForFenceValue(uint64 fenceValue);
	uint32 getFrameResourceCount() const;
	uint64 getFenceValue() const;
	uint64 getCompletedValue() const;
	DirectContextProxy createDirectContextProxy();
	void startNewFrame();
	void flushCommandQueue();
	void destroy();
	~CommandQueue();
protected:
	friend class CommandList;
	FrameResourceQueue *getFrameResourceQueue();
private:
	uint64                              _fenceValue;
	std::weak_ptr<Device>               _pDevice;
	D3D12_COMMAND_LIST_TYPE             _queueType;
	WRL::ComPtr<ID3D12Fence>            _pFence;
	WRL::ComPtr<ID3D12CommandQueue>     _pCommandQueue;
	std::unique_ptr<FrameResourceQueue> _pFrameResourceQueue;
	std::vector<ContextProxy>			_delayExecutedContextProxy;
};

}