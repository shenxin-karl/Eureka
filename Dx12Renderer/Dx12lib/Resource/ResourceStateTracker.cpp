#include <iostream>
#include <Dx12lib/Resource/IResource.h>
#include <Dx12lib/Resource/ResourceStateTracker.h>
#include <Dx12lib/Context/CommandList.h>
#include <Dx12lib/Context/ContextProxy.hpp>

namespace dx12lib {

ResourceStateTracker::ResourceStateTracker(std::weak_ptr<Device> pDevice) : _pDevice(pDevice) {
}

void ResourceStateTracker::resourceBarrier(const D3D12_RESOURCE_BARRIER &expectBarrier) {
	if (expectBarrier.Type == D3D12_RESOURCE_BARRIER_TYPE_TRANSITION) {
		const D3D12_RESOURCE_TRANSITION_BARRIER &expectTransition = expectBarrier.Transition;
		const auto iter = _finalResourceState.find(expectTransition.pResource);
		if (iter != _finalResourceState.end()) {	// 状态已知的情况
			auto &finalResourceState = iter->second;
			// 内部的 subResource 不统一
			if (expectTransition.Subresource == D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES &&
				!finalResourceState._subResourceState.empty())
			{
				for (auto subresourceState : finalResourceState._subResourceState) {
					if (expectTransition.StateAfter != subresourceState.second) {
						D3D12_RESOURCE_BARRIER newBarrier = expectBarrier;
						newBarrier.Transition.Subresource = subresourceState.first;
						newBarrier.Transition.StateBefore = subresourceState.second;
						_resourceBarriers.push_back(newBarrier);
					}
				}
			} else {	// 整个 resource 都转换为 expectBarrier 状态
				auto finalState = finalResourceState.getSubResourceState(expectTransition.Subresource);
				if (finalState != expectTransition.StateAfter) {
					D3D12_RESOURCE_BARRIER newBarrier = expectBarrier;
					newBarrier.Transition.StateBefore = finalState;
					_resourceBarriers.push_back(newBarrier);
				}
			}
		} else {	
			_pendingResourceBarriers.push_back(expectBarrier);
		}
		auto &finalResourceStateRecord = _finalResourceState[expectTransition.pResource];
		finalResourceStateRecord.setSubResourceState(expectTransition.Subresource, expectTransition.StateAfter);
	} else {
		_resourceBarriers.push_back(expectBarrier);
	}
}

D3D12_RESOURCE_STATES ResourceStateTracker::getResourceState(ID3D12Resource *pResource, UINT subResource) {
	if (auto iter = _finalResourceState.find(pResource); iter != _finalResourceState.end())
		return iter->second.getSubResourceState(subResource);

	auto *pGlobalResourceState = getGlobalResourceState();
	ResourceState *pResourceState = (pGlobalResourceState != nullptr) ?
		pGlobalResourceState->findResourceState(pResource) : nullptr;

	if (pResourceState != nullptr)
		return pResourceState->getSubResourceState(subResource);

	assert(false);
	return D3D12_RESOURCE_STATE_COMMON;
}

void ResourceStateTracker::transitionResource(ID3D12Resource *pResource, 
                                              D3D12_RESOURCE_STATES stateAfter, 
                                              UINT subResource /*= D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES */) 
{
	resourceBarrier(CD3DX12_RESOURCE_BARRIER::Transition(
		pResource,
		D3D12_RESOURCE_STATE_COMMON,
		stateAfter,
		subResource
	));
}

void ResourceStateTracker::UAVBarrier(const IResource *pResource /*= nullptr*/) {
	auto *pD3DResource = pResource != nullptr ? pResource->getD3DResource().Get() : nullptr;
	assert(pD3DResource != nullptr);
	resourceBarrier(CD3DX12_RESOURCE_BARRIER::UAV(pD3DResource));
}

void ResourceStateTracker::aliasBarrier(const IResource *pBefore, const IResource *pAfter) {
	auto *pD3DBeforeResource = pBefore != nullptr ? pBefore->getD3DResource().Get() : nullptr;
	auto *pD3DAfterResource = pAfter != nullptr ? pAfter->getD3DResource().Get() : nullptr;
	if (pD3DBeforeResource == nullptr || pD3DAfterResource == nullptr) {
		assert(false);
		std::cout << __FUNCTION__ << " pD3DBeforeResource == nullptr || pD3DAfterResource == nullptr" << std::endl;
		return;
	}
	resourceBarrier(CD3DX12_RESOURCE_BARRIER::Aliasing(pD3DBeforeResource, pD3DAfterResource));
}

uint32 ResourceStateTracker::flushResourceBarriers(CommandList *pCmdList) {
	UINT numBarrier = static_cast<UINT>(_resourceBarriers.size());
	if (numBarrier > 0) {
		pCmdList->getD3DCommandList()->ResourceBarrier(numBarrier, _resourceBarriers.data());
		_resourceBarriers.clear();
	}
	return numBarrier;
}

void ResourceStateTracker::commitFinalResourceStates() {
	auto *pGlobalResourceState = getGlobalResourceState();
	assert(pGlobalResourceState->isLocked());
	for (auto &&[pResource, state] : _finalResourceState) {
		if (pGlobalResourceState != nullptr)
			pGlobalResourceState->setResourceState(pResource, state);
	}
	_finalResourceState.clear();
}

UINT ResourceStateTracker::flushPendingResourceBarriers(std::shared_ptr<CommandList> pCmdList) {
	auto *pGlobalResourceState = getGlobalResourceState();
	assert(pGlobalResourceState->isLocked());

	std::vector<D3D12_RESOURCE_BARRIER> resourceBarriers;
	resourceBarriers.reserve(_pendingResourceBarriers.size());
	for (auto &pendingBarrier : _pendingResourceBarriers) {
		if (pendingBarrier.Type == D3D12_RESOURCE_BARRIER_TYPE_TRANSITION) {
			const auto &pendingTransition = pendingBarrier.Transition;

			ResourceState *pResourceState = nullptr;
			if (pGlobalResourceState == nullptr || 
				(pResourceState = pGlobalResourceState->findResourceState(pendingTransition.pResource)) == nullptr) 
			{
				assert(false && "Unknown resource status");
				continue;
			}

			const auto &currResourceState = *pResourceState;
			if (pendingTransition.Subresource == D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES &&
				!currResourceState._subResourceState.empty())
			{
				for (auto &&[subResource, state] : currResourceState._subResourceState) {
					if (pendingTransition.StateAfter != state) {
						auto newBarrier = pendingBarrier;
						newBarrier.Transition.Subresource = subResource;
						newBarrier.Transition.StateBefore = state;
						resourceBarriers.push_back(newBarrier);
					}
				}
			} else {	// Uniform subResource status	
				if (currResourceState._state != pendingTransition.StateAfter) {
					auto newBarrier = pendingBarrier;
					newBarrier.Transition.StateBefore = currResourceState._state;
					resourceBarriers.push_back(newBarrier);
				}
			}
		}
	}
	_pendingResourceBarriers.clear();

	UINT numBarriers = static_cast<UINT>(resourceBarriers.size());
	if (numBarriers > 0) {
		pCmdList->getD3DCommandList()->ResourceBarrier(
			numBarriers, 
			resourceBarriers.data()
		);
	}
	return numBarriers;
}

void ResourceStateTracker::reset() {
	_pendingResourceBarriers.clear();
	_resourceBarriers.clear();
	_finalResourceState.clear();
}

GlobalResourceState * ResourceStateTracker::getGlobalResourceState() const {
	if (auto pSharedDevice = _pDevice.lock())
		return pSharedDevice->getGlobalResourceState();
	return nullptr;
}

ResourceStateTracker::ResourceState::ResourceState(D3D12_RESOURCE_STATES state /*= D3D12_RESOURCE_STATE_COMMON*/)
: _state(state) {
}

void ResourceStateTracker::ResourceState::setSubResourceState(UINT subResource, D3D12_RESOURCE_STATES state) {
	if (subResource == D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES) {
		_state = state;
		_subResourceState.clear();
	} else {
		_subResourceState[subResource] = state;
	}
}

D3D12_RESOURCE_STATES ResourceStateTracker::ResourceState::getSubResourceState(UINT subResource) {
	auto state = _state;
	if (auto iter = _subResourceState.find(subResource); iter != _subResourceState.end())
		state = iter->second;
	return state;
}

void GlobalResourceState::lock() {
	_mutex.lock();
	_isLocked = true;
}

void GlobalResourceState::unlock() {
	_mutex.unlock();
	_isLocked = false;
}

void GlobalResourceState::addGlobalResourceState(ID3D12Resource *pResource, D3D12_RESOURCE_STATES state) {
	if (pResource != nullptr) {
		std::lock_guard lock(_mutex);
		_resourceState[pResource].setSubResourceState(D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES, state);
	}
}

void GlobalResourceState::removeGlobalResourceState(ID3D12Resource *pResource) {
	if (pResource != nullptr) {
		std::lock_guard lock(_mutex);
		_resourceState.erase(pResource);
	}
}

void GlobalResourceState::setResourceState(ID3D12Resource *pResource, const ResourceState &state) {
	_resourceState[pResource] = state;
}

const GlobalResourceState::ResourceState *GlobalResourceState::findResourceState(
	ID3D12Resource *pResource) const
{
	return const_cast<GlobalResourceState *>(this)->findResourceState(pResource);
}

GlobalResourceState::ResourceState * GlobalResourceState::findResourceState(ID3D12Resource *pResource) {
	auto iter = _resourceState.find(pResource);
	if (iter != _resourceState.end())
		return &iter->second;
	return nullptr;
}

bool GlobalResourceState::isLocked() const {
	return _isLocked;
}

}
