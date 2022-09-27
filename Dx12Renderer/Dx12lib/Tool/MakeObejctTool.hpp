#pragma once
#include <Dx12lib/dx12libStd.h>
#include <type_traits>

namespace dx12libTool {

using namespace dx12lib;

template<typename T>
class _MakeObjectTool : public T {
public:
	using Type = T;
	template<typename...Args> 
	_MakeObjectTool(Args&&...args) : T(std::forward<Args>(args)...) {}
};

// Context
using MakeCommandList = _MakeObjectTool<CommandList>;
using MakeCommandQueue = _MakeObjectTool<CommandQueue>;
using MakeFrameResourceItem = _MakeObjectTool<FrameResourceItem>;
using MakeFrameResourceQueue = _MakeObjectTool<FrameResourceQueue>;

// Descriptor
using MakeDescriptorAllocation = _MakeObjectTool<DescriptorAllocation>;
using MakeDescriptorAllocatorPage= _MakeObjectTool<DescriptorAllocatorPage>;
using MakeDescriptorAllocator = _MakeObjectTool<DescriptorAllocator>;
using MakeDynamicDescriptorHeap = _MakeObjectTool<DynamicDescriptorHeap>;

// Device
using MakeSwapChain = _MakeObjectTool<SwapChain>;

// Resource
using MakeResourceStateTracker = _MakeObjectTool<ResourceStateTracker>;

// Pipeline
using MakeRootSignature = _MakeObjectTool<RootSignature>;
using MakeGraphicsPSO = _MakeObjectTool<GraphicsPSO>;
using MakeComputePSO = _MakeObjectTool<ComputePSO>;

// Buffer
using MakeConstantBuffer = _MakeObjectTool<ConstantBuffer>;
using MakeIndexBuffer = _MakeObjectTool<IndexBuffer>;
using MakeVertexBuffer = _MakeObjectTool<VertexBuffer>;
using MakeSRStructuredBuffer = _MakeObjectTool<SRStructuredBuffer>;
using MakeReadBackBuffer = _MakeObjectTool<ReadBackBuffer>;

template<typename T>
using MakeFRConstantBuffer = _MakeObjectTool<FRConstantBuffer<T>>;

using MakeFRRawConstantBuffer = _MakeObjectTool<FRConstantBuffer<RawData>>;

using MakeFRRawSRStructuredBuffer = _MakeObjectTool<FRSRStructuredBuffer<RawData>>;

template<typename T>
using MakeFRSRStructuredBuffer = _MakeObjectTool<FRSRStructuredBuffer<T>>;
using MakeUAStructuredBuffer = _MakeObjectTool<UAStructuredBuffer>;
using MakeTexture = _MakeObjectTool<Texture>;

}