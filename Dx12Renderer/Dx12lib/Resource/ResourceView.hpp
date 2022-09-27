#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Descriptor/DescriptorAllocation.h>
#include <functional>

namespace dx12lib {

enum class ViewType {
	RenderTarget	= 0,
	DepthStencil	= 1,
	ConstantBuffer  = 2,
	ShaderResource	= 3,
	UnorderedAccess = 4,
};

template<ViewType Type>
class ResourceView {
public:
	ResourceView() = default;
	ResourceView(const ResourceView &) = default;
	ResourceView(ResourceView &&) noexcept = default;
	ResourceView &operator=(const ResourceView &) = default;
	ResourceView &operator=(ResourceView &&) noexcept = default;
	ResourceView(const DescriptorAllocation &descriptor, const IResource *pResource, size_t offset = 0)
	: _offset(offset), _descriptor(descriptor), _pResource(pResource)
	{
		assert(offset < descriptor.getNumHandle());
	}
	D3D12_CPU_DESCRIPTOR_HANDLE getCPUDescriptorHandle() const {
		return _descriptor.getCPUHandle(_offset);
	}
	operator D3D12_CPU_DESCRIPTOR_HANDLE() const {
		return getCPUDescriptorHandle();
	}
	const IResource *getResource() const {
		return _pResource;
	}
	bool valid() const {
		return _descriptor.isValid();
	}
private:
	size_t _offset = 0;
	DescriptorAllocation _descriptor;
	const IResource *_pResource = nullptr;
};

template<typename T>
class BufferView {
	friend class CommandList;
public:
	BufferView() = default;

	template<typename ... Args> requires(sizeof...(Args) > 0)
	BufferView(Args&&...args) : _view(std::forward<Args>(args)...) {}
	BufferView(D3D12_VERTEX_BUFFER_VIEW view) : _view(view) {}
	BufferView(const BufferView &) = default;
	BufferView(BufferView &&) noexcept = default;
	BufferView &operator=(const BufferView &) = default;
	BufferView &operator=(BufferView &&) noexcept = default;
	operator T() const {
		return _view;
	}
	T *operator&() {
		return &_view;
	}
	const T *operator&() const {
		return &_view;
	}
private:
	T _view;
};

using RenderTargetView = ResourceView<ViewType::RenderTarget>;
using DepthStencilView = ResourceView<ViewType::DepthStencil>;
using ConstantBufferView = ResourceView<ViewType::ConstantBuffer>;
using ShaderResourceView = ResourceView<ViewType::ShaderResource>;
using StructuredBufferView = ResourceView<ViewType::ShaderResource>;
using UnorderedAccessView = ResourceView<ViewType::UnorderedAccess>;
using VertexBufferView = BufferView<D3D12_VERTEX_BUFFER_VIEW>;
using IndexBufferView = BufferView<D3D12_INDEX_BUFFER_VIEW>;

template<typename T>
class ViewManager {
public:
	ViewManager() {
		for (auto &idx : _viewIndices)
			idx = kMaxMipLevel;
	}
	ViewManager(const ViewManager &) = delete;
	ViewManager(ViewManager &&) = default;
	ViewManager &operator=(const ViewManager &) = delete;
	ViewManager &operator=(ViewManager &&) = default;

	bool exist(size_t mipSlice) const noexcept {
		assert(mipSlice < kMaxMipLevel);
		return _viewIndices[mipSlice] != kMaxMipLevel;
	}

	void set(size_t mipSlice, const T &view) noexcept {
		assert(mipSlice < kMaxMipLevel);
		uint32_t index = static_cast<uint32_t>(_viewArray.size());
		_viewIndices[mipSlice] = index;
		_viewArray.emplace_back(view);
	}

	const T &get(size_t mipSlice) const noexcept {
		assert(mipSlice < kMaxMipLevel);
		assert(_viewIndices[mipSlice] != kMaxMipLevel);
		return _viewArray[_viewIndices[mipSlice]];
	}
private:
	constexpr static size_t kMaxMipLevel = 16;
	std::vector<T> _viewArray;
	std::array<uint32_t, kMaxMipLevel> _viewIndices;
};

}
