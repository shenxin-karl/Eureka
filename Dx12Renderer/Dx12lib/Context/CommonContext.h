#pragma once
#include <memory>
#include <Math/MathStd.hpp>
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Resource/IResource.h>
#include <Dx12lib/Tool/MakeObejctTool.hpp>
#include <Dx12lib/Buffer/FRConstantBuffer.hpp>
#include <Dx12lib/Tool/RenderProfiler.hpp>

namespace dx12lib {

interface IContext {
	IContext() = default;
	IContext(const IContext &) = delete;
	IContext &operator=(const IContext &) = delete;
	virtual std::weak_ptr<Device> getDevice() const = 0;
	virtual ID3D12GraphicsCommandList *getD3DCommandList() const noexcept = 0;
	virtual std::shared_ptr<CommandList> getCommandList() noexcept = 0;
	virtual const RenderProfiler &getRenderProfiler() const noexcept = 0;
	virtual ~IContext() = default;
};

interface ICommonContext : IContext {
	virtual void trackResource(std::shared_ptr<IResource> &&pResource) = 0;
	virtual std::shared_ptr<Texture> createTextureFromFile(const std::wstring &fileName, bool sRGB = false, size_t genMip = 0) = 0;
	virtual std::shared_ptr<Texture> createTextureFromMemory(const std::string &extension, const void *pData, size_t sizeInByte, bool sRGB = false, size_t genMip = 0) = 0;

	virtual	void setDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, WRL::ComPtr<ID3D12DescriptorHeap> pHeap) = 0;
	virtual void setConstantBufferView(const ShaderRegister &sr, const ConstantBufferView &crv) = 0;
	virtual void setConstantBufferView(const std::string &boundResourceName, const ConstantBufferView &cbv) = 0;
	virtual void setShaderResourceView(const ShaderRegister &sr, const ShaderResourceView &srv) = 0;
	virtual void setShaderResourceView(const std::string &boundResourceName, const ShaderResourceView &srv, size_t offset = 0, size_t numDescriptor = 1) = 0;
	virtual void readBack(std::shared_ptr<ReadBackBuffer> pReadBackBuffer) = 0;

	virtual void copyResourceImpl(std::shared_ptr<IResource> pDest, std::shared_ptr<IResource> pSrc) = 0;
	virtual void transitionBarrierImpl(std::shared_ptr<IResource> pBuffer, D3D12_RESOURCE_STATES state, UINT subResource, bool flushBarrier) = 0;
	virtual void aliasBarrierImpl(std::shared_ptr<IResource> pBefore, std::shared_ptr<IResource> pAfter, bool flushBarrier) = 0;
	virtual void flushResourceBarriers() = 0;

	template<typename T1, typename T2> requires(std::is_base_of_v<IResource, T1> &&std::is_base_of_v<IResource, T2>)
	void copyResource(std::shared_ptr<T1> pDest, std::shared_ptr<T2> pSrc) {
		this->copyResourceImpl(
			std::static_pointer_cast<IResource>(pDest),
			std::static_pointer_cast<IResource>(pSrc)
		);
	}

	template<typename T> requires(std::is_base_of_v<IResource, T>)
	void transitionBarrier(std::shared_ptr<T> pBuffer, D3D12_RESOURCE_STATES state, UINT subResource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES, bool flushBarrier = false) {
		this->transitionBarrierImpl(
			std::static_pointer_cast<IResource>(pBuffer),
			state,
			subResource,
			flushBarrier
		);
	}

	template<typename T1, typename T2> requires(std::is_base_of_v<IResource, T1> &&std::is_base_of_v<IResource, T2>)
	void aliasBarrier(std::shared_ptr<T1> pBefore, std::shared_ptr<T2> pAfter, bool flushBarrier = false) {
		this->aliasBarrierImpl(
			std::static_pointer_cast<IResource>(pBefore),
			std::static_pointer_cast<IResource>(pAfter),
			flushBarrier
		);
	}


	/////////////////////////////////// ConstantBuffer //////////////////////////////////
#if 1
	template<typename T>
	std::shared_ptr<ConstantBuffer> createConstantBuffer() {
		return std::make_shared<dx12libTool::MakeConstantBuffer>(
			getDevice(),
			nullptr,
			sizeof(T)
		);
	}

	template<typename...Args>
	std::shared_ptr<ConstantBuffer> createConstantBuffer(Args&&...args) {
		return std::make_shared<dx12libTool::MakeConstantBuffer>(
			getDevice(),
			std::forward<Args>(args)...
		);
	}

 	template<typename T, typename...Args>
	std::shared_ptr<FRConstantBuffer<T>> createFRConstantBuffer(Args&&...args) {
		return std::make_shared<dx12libTool::MakeFRConstantBuffer<T>>(
			getDevice(),
			std::forward<Args>(args)...
		);
	}

	template<typename...Args>
	std::shared_ptr<FRConstantBuffer<RawData>> createFRRawConstantBuffer(Args&&...args) {
		return std::make_shared<dx12libTool::MakeFRRawConstantBuffer>(
			getDevice(),
			std::forward<Args>(args)...
		);
	}

	template<typename T> requires(std::is_base_of_v<IConstantBuffer, T> || std::is_same_v<IConstantBuffer, T>)
	void setConstantBuffer(const ShaderRegister &sr, const std::shared_ptr<T> &pBuffer) {
		auto pConstantBuffer = static_cast<IConstantBuffer *>(pBuffer.get());
		this->setConstantBufferView(sr, pConstantBuffer->getCBV());
	}
#endif
	/////////////////////////////////// SRStructuredBuffer //////////////////////////////////
#if 1
	template<typename... Args>
	std::shared_ptr<SRStructuredBuffer> createStructuredBuffer(Args&&...args) {
		return std::make_shared<dx12libTool::MakeSRStructuredBuffer>(
			getDevice(),
			std::forward<Args>(args)...
		);
	}

	template<typename T, typename...Args>
	std::shared_ptr<FRSRStructuredBuffer<T>> createFRStructuredBuffer(Args&&...args) {
		return std::make_shared<dx12libTool::MakeFRSRStructuredBuffer<T>>(
			getDevice(),
			std::forward<Args>(args)...
		);
	}

	template<typename...Args>
	std::shared_ptr<FRSRStructuredBuffer<RawData>> createFRRawStructuredBuffer(Args&&...args) {
		return std::make_shared<dx12libTool::MakeFRRawSRStructuredBuffer>(
			getDevice(),
			std::forward<Args>(args)...
		);
	}

	template<typename T> requires(std::is_base_of_v<ISRStructuredBuffer, T>)
	void setStructuredBuffer(const ShaderRegister &sr, const std::shared_ptr<T> &pBuffer) {
		auto pStructuredBuffer = static_cast<ISRStructuredBuffer *>(pBuffer.get());
		this->setShaderResourceView(sr, pStructuredBuffer->getSRV());
	}
#endif
	/////////////////////////////////// ReadBackBuffer //////////////////////////////////
#if 1
	template<typename... Args>
	std::shared_ptr<ReadBackBuffer> createReadBackBuffer(Args&&... args) {
		return std::make_shared<dx12libTool::MakeReadBackBuffer>(
			getDevice(),
			std::forward<Args>(args)...
		);
	}
#endif

#if 1
	/////////////////////////////////// Texture //////////////////////////////////
	template<typename ...Args>
	std::shared_ptr<Texture> createTexture(Args&&... args) {
		return std::make_shared<dx12libTool::MakeTexture>(getDevice(), std::forward<Args>(args)...);
	}
#endif
};

interface IGraphicsContext : virtual ICommonContext {
	virtual std::shared_ptr<VertexBuffer> createVertexBuffer(const void *pData, size_t numElements, size_t stride) = 0;
	virtual std::shared_ptr<IndexBuffer> createIndexBuffer(const void *pData, size_t numElements, DXGI_FORMAT indexFormat) = 0;

	virtual void setViewport(const D3D12_VIEWPORT &viewport) = 0;
	virtual void setScissorRect(const D3D12_RECT &rect) = 0;
	virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer> &pVertBuffer, UINT slot = 0) = 0;
	virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer> &pIndexBuffer) = 0;
	virtual void setGraphicsPSO(std::shared_ptr<GraphicsPSO> pPipelineStateObject) = 0;
	virtual void setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology) = 0;
	virtual void setStencilRef(UINT stencilRef) = 0;
	virtual void setGraphics32BitConstants(const ShaderRegister &sr, size_t numConstants, const void *pData, size_t destOffset = 0) = 0;
	virtual void setRenderTarget(const RenderTargetView &rtv, const DepthStencilView &dsv) = 0;
	virtual void setRenderTarget(const DepthStencilView &dsv) = 0;
	virtual void setRenderTarget(const RenderTargetView &rtv) = 0;
	virtual void setRenderTargets(const std::vector<RenderTargetView> &rtvs, const DepthStencilView &dsv) = 0;

	virtual void drawInstanced(size_t vertCount, size_t instanceCount, size_t baseVertexLocation, size_t startInstanceLocation = 0) = 0;
	virtual void drawIndexedInstanced(size_t indexCountPerInstance, size_t instanceCount, size_t startIndexLocation, size_t baseVertexLocation, size_t startInstanceLocation) = 0;

	virtual void clearColor(const RenderTargetView &rtv, Math::float4 color) = 0;
	virtual void clearColor(const RenderTargetView &rtv, const float colors[4]) = 0;
	virtual void clearDepth(const DepthStencilView &dsv, float depth) = 0;
	virtual void clearStencil(const DepthStencilView &dsv, UINT stencil) = 0;
	virtual void clearDepthStencil(const DepthStencilView &dsv, float depth, UINT stencil) = 0;

	virtual void beginEvent(const std::string &eventName) = 0;
	virtual void endEvent() = 0;
};

interface IComputeContext : virtual ICommonContext {
	virtual void setComputePSO(std::shared_ptr<ComputePSO> pPipelineStateObject) = 0;
	virtual void setUnorderedAccessView(const ShaderRegister &sr, const UnorderedAccessView &uav) = 0;
	virtual void setUnorderedAccessView(const std::string &boundResourceName, const UnorderedAccessView &uav, size_t offset = 0, size_t numDescriptors = 1) = 0;
	virtual void generateMips(std::shared_ptr<Texture> pTexture) = 0;
	virtual void setCompute32BitConstants(const ShaderRegister &sr, size_t numConstants, const void *pData, size_t destOffset = 0) = 0;
	virtual void dispatch(size_t GroupCountX = 1, size_t GroupCountY = 1, size_t GroupCountZ = 1) = 0;
	virtual void UAVBarrier(const std::shared_ptr<IResource> &pResource, bool flushBarriers) = 0;

	void dispatch(std::array<size_t, 3> dispatchArgs) noexcept {
		dispatch(dispatchArgs[0], dispatchArgs[1], dispatchArgs[2]);
	}

	/////////////////////////////////// UAStructuredBuffer //////////////////////////////////
#if 1
	template<typename...Args>
	std::shared_ptr<UAStructuredBuffer> createUAStructuredBuffer(Args&&...args) {
		return std::make_shared<dx12libTool::MakeUAStructuredBuffer>(
			getDevice(),
			getCommandList(),
			std::forward<Args>(args)...
		);
	}
#endif
};

interface IDirectContext : IGraphicsContext, IComputeContext {
};

}