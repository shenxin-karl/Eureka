#pragma once
#include <optional>
#include <Dx12lib/dx12libStd.h>

namespace dx12lib {


class GlobalResourceState;
class ResourceStateTracker {
protected:
	explicit ResourceStateTracker(std::weak_ptr<Device> pDevice);
public:
	~ResourceStateTracker() = default;
	void resourceBarrier(const D3D12_RESOURCE_BARRIER &barrier);
	D3D12_RESOURCE_STATES getResourceState(ID3D12Resource *pResource, UINT subResource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
	void transitionResource(ID3D12Resource *pResource,
		D3D12_RESOURCE_STATES stateAfter, 
		UINT subResource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES
	);
	void UAVBarrier(const IResource *resource = nullptr);
	void aliasBarrier(const IResource *pBefore, const IResource *pAfter);
	uint32 flushResourceBarriers(CommandList *pCmdList);
	void commitFinalResourceStates();
	UINT flushPendingResourceBarriers(std::shared_ptr<CommandList> pCmdList);
	void reset();
	GlobalResourceState *getGlobalResourceState() const;
private:
	friend class GlobalResourceState;
	struct ResourceState {
		explicit ResourceState(D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_COMMON);
		void setSubResourceState(UINT subResource, D3D12_RESOURCE_STATES state);
		D3D12_RESOURCE_STATES getSubResourceState(UINT subResource);
	public:
		D3D12_RESOURCE_STATES                  _state;
		std::map<UINT, D3D12_RESOURCE_STATES>  _subResourceState;
	};
	using ResourceBarriers = std::vector<D3D12_RESOURCE_BARRIER>;
	using ResourceStateMap = std::unordered_map<ID3D12Resource *, ResourceState>;
private:
	std::weak_ptr<Device> _pDevice;
	ResourceBarriers      _pendingResourceBarriers;
	ResourceBarriers      _resourceBarriers;
	ResourceStateMap      _finalResourceState;
};


class GlobalResourceState {
	using ResourceState = ResourceStateTracker::ResourceState;
	using ResourceStateMap = ResourceStateTracker::ResourceStateMap;
public:
	void lock();
	void unlock();
	void addGlobalResourceState(ID3D12Resource *pResource, D3D12_RESOURCE_STATES state);
	void removeGlobalResourceState(ID3D12Resource *pResource);
	void setResourceState(ID3D12Resource *pResource, const ResourceState &state);
	const ResourceState *findResourceState(ID3D12Resource *pResource) const;
	ResourceState *findResourceState(ID3D12Resource *pResource);
	bool isLocked() const;
private:
	bool              _isLocked = false;
	std::mutex        _mutex;
	ResourceStateMap  _resourceState;
};

}