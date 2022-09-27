#include <Dx12lib/Context/CommandList.h>
#include <Dx12lib/Context/FrameResourceQueue.h>
#include <Dx12lib/Device/Device.h>
#include <Dx12lib/Tool/MakeObejctTool.hpp>

namespace dx12lib {

FrameResourceItem::FrameResourceItem(std::weak_ptr<Device> pDevice, D3D12_COMMAND_LIST_TYPE cmdListType, uint32 frameIndex)
: _fence(0), _frameIndex(frameIndex), _pDevice(pDevice), _cmdListType(cmdListType) {
}

uint64 FrameResourceItem::getFence() const noexcept {
	return _fence;
}

void FrameResourceItem::setFence(uint64 fence) noexcept {
	_fence = fence;
}

std::shared_ptr<CommandList> FrameResourceItem::createCommandList() {
	std::shared_ptr<CommandList> pCmdList;
	if (_availableCmdList.empty()) {
		pCmdList = std::make_shared<dx12libTool::MakeCommandList>(weak_from_this());
		_cmdListPool.push_back(pCmdList);
		pCmdList->close();
		pCmdList->reset();
		return pCmdList;
	} else {
		pCmdList = _availableCmdList.back();
		_availableCmdList.pop_back();
		assert(!pCmdList->shouldReset());
		return pCmdList;
	}
}

std::weak_ptr<Device> FrameResourceItem::getDevice() const noexcept {
	return _pDevice;
}

D3D12_COMMAND_LIST_TYPE FrameResourceItem::getCommandListType() const noexcept {
	return _cmdListType;
}

void FrameResourceItem::newFrame(uint64 fence) {
	_availableCmdList = _cmdListPool;
	for (auto &pCmdList : _cmdListPool) {
		if (pCmdList->shouldReset())
			pCmdList->reset();
	}
	setFence(fence);
}

uint32 FrameResourceItem::getFrameIndex() const {
	return _frameIndex;
}

void FrameResourceItem::destroy() {
	for (auto &pCmdList : _cmdListPool) {
		if (pCmdList->shouldReset())
			pCmdList->reset();
	}
}

FrameResourceQueue::FrameResourceQueue(std::weak_ptr<Device> pDevice, D3D12_COMMAND_LIST_TYPE cmdListType) {
	_frameResourceItemCount = cmdListType == D3D12_COMMAND_LIST_TYPE_DIRECT ? kFrameResourceCount : 1;
	for (uint32 i = 0; i < _frameResourceItemCount; ++i)
		_frameResourceQueue[i] = std::make_shared<dx12libTool::MakeFrameResourceItem>(pDevice, cmdListType, i);
}

std::shared_ptr<CommandList> FrameResourceQueue::createCommandList() {
	return _frameResourceQueue[FrameIndexProxy::getConstantFrameIndexRef()]->createCommandList();
}

uint32 FrameResourceQueue::getMaxFrameResourceCount() const noexcept {
	return _frameResourceItemCount;
}

void FrameResourceQueue::newFrame(uint64 fence) {
	FrameIndexProxy::startNewFrame();
	_frameResourceQueue[FrameIndexProxy::getConstantFrameIndexRef()]->newFrame(fence);
}

std::shared_ptr<FrameResourceItem> FrameResourceQueue::getCurrentFrameResourceItem() const {
	return _frameResourceQueue[FrameIndexProxy::getConstantFrameIndexRef()];
}

void FrameResourceQueue::destroy() {
	for (auto &pFrameResourceItem : _frameResourceQueue)
		pFrameResourceItem->destroy();
}

}
