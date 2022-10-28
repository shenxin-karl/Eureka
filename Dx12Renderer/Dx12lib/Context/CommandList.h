#pragma once
#include <Dx12lib/dx12libStd.h>
#include <Dx12lib/Context/ContextProxy.hpp>
#include <Dx12lib/Context/CommonContext.h>
#include <DirectXTex/DirectXTex/DirectXTex.h>
#include <memory>

namespace dx12lib {

class CommandList : public std::enable_shared_from_this<CommandList>, public IDirectContext {
protected:
	CommandList(std::weak_ptr<FrameResourceItem> pFrameResourceItem);
public:
	~CommandList() override;
/// Context api
	std::weak_ptr<Device> getDevice() const final;
	ID3D12GraphicsCommandList *getD3DCommandList() const noexcept final;
	std::shared_ptr<CommandList> getCommandList() noexcept final;
	const RenderProfiler &getRenderProfiler() const noexcept final;

/// CommonContext api
	void trackResource(std::shared_ptr<IResource> &&pResource) final;
	std::shared_ptr<Texture> createTextureFromFile(const std::wstring &fileName, bool sRGB, size_t genMip) final;
	std::shared_ptr<Texture> createTextureFromMemory(const std::string &extension, const void *pData, size_t sizeInByte, bool sRGB, size_t genMip) final;

	void setDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, WRL::ComPtr<ID3D12DescriptorHeap> pHeap) final;
	void setConstantBufferView(const ShaderRegister &sr, const ConstantBufferView &cbv) final;
	void setConstantBufferView(const std::string &boundResourceName, const ConstantBufferView &cbv) final;
	void setShaderResourceView(const ShaderRegister &sr, const ShaderResourceView &srv) final;
	void setShaderResourceView(const std::string &boundResourceName, const ShaderResourceView &srv, size_t offset, size_t numDescriptors) final;
	void readBack(std::shared_ptr<ReadBackBuffer> pReadBackBuffer) final;

	void copyResourceImpl(std::shared_ptr<IResource> pDest, std::shared_ptr<IResource> pSrc) final;
	void transitionBarrierImpl(std::shared_ptr<IResource> pBuffer, D3D12_RESOURCE_STATES state, UINT subResource, bool flushBarrier) final;
	void aliasBarrierImpl(std::shared_ptr<IResource> pBefore, std::shared_ptr<IResource> pAfter, bool flushBarrier) final;
	void flushResourceBarriers() final;

/// GraphicsContext api
	std::shared_ptr<VertexBuffer> createVertexBuffer(const void *pData, size_t numElements, size_t stride) final;
	std::shared_ptr<IndexBuffer> createIndexBuffer(const void *pData, size_t numElements, DXGI_FORMAT indexFormat) final;

	void setViewport(const D3D12_VIEWPORT &viewport) final;
	void setScissorRect(const D3D12_RECT &rect) final;
	void setVertexBuffer(const std::shared_ptr<VertexBuffer> &pVertBuffer, UINT slot) final;
	void setIndexBuffer(const std::shared_ptr<IndexBuffer> &pIndexBuffer) final;
	void setGraphicsPSO(std::shared_ptr<GraphicsPSO> pPipelineStateObject) final;
	void setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology) final;
	void setStencilRef(UINT stencilRef) final;
	void setGraphics32BitConstants(const ShaderRegister &sr, size_t numConstants, const void *pData, size_t destOffset) final;
	void setRenderTarget(const RenderTargetView &rtv, const DepthStencilView &dsv) final;
	void setRenderTarget(const RenderTargetView &rtv) final;
	void setRenderTarget(const DepthStencilView &dsv) final;
	void setRenderTargets(const std::vector<RenderTargetView> &rtvs, const DepthStencilView &dsv) final;

	void drawInstanced(size_t vertCount, size_t instanceCount, size_t baseVertexLocation, size_t startInstanceLocation) final;
	void drawIndexedInstanced(size_t indexCountPerInstance, size_t instanceCount, size_t startIndexLocation, size_t baseVertexLocation, size_t startInstanceLocation) final;

	void clearColor(const RenderTargetView &rtv, Math::float4 color) final;
	void clearColor(const RenderTargetView &rtv, const float colors[4]) final;
	void clearDepth(const DepthStencilView &dsv, float depth) final;
	void clearStencil(const DepthStencilView &dsv, UINT stencil) final;
	void clearDepthStencil(const DepthStencilView &dsv, float depth, UINT stencil) final;

	void beginEvent(const std::string &eventName) override;
	void endEvent() override;
/// ComputeContext api 
	void setComputePSO(std::shared_ptr<ComputePSO> pPipelineStateObject) final;
	void setUnorderedAccessView(const ShaderRegister &sr, const UnorderedAccessView &uav) final;
	void setUnorderedAccessView(const std::string &boundResourceName, const UnorderedAccessView &uav, size_t offset = 0, size_t numDescriptors = 1) final;
	void setCompute32BitConstants(const ShaderRegister &sr, size_t numConstants, const void *pData, size_t destOffset) final;
	void generateMips(std::shared_ptr<Texture> pTexture) final;
	void dispatch(size_t GroupCountX, size_t GroupCountY, size_t GroupCountZ) final;
	void UAVBarrier(const std::shared_ptr<IResource> &pResource, bool flushBarriers) final;

private:
	friend class CommandQueue;
	friend class FrameResourceItem;
	using ReadBackBufferPool = std::vector<std::shared_ptr<ReadBackBuffer>>;
	using StaleResourcePool = std::vector<std::shared_ptr<IResource>>;
	using StaleRawObjectPool = std::vector<WRL::ComPtr<ID3D12Object>>;
	using StaleRawResourcePool = std::vector<WRL::ComPtr<ID3D12Resource>>;
	void setGraphicsRootSignature(std::shared_ptr<RootSignature> pRootSignature);
	void setComputeRootSignature(std::shared_ptr<RootSignature> pRootSignature);
	void close();
	void close(std::shared_ptr<CommandList> pPendingCmdList);
	void reset();
	using SetRootSignatureFunc = std::function<void(ID3D12GraphicsCommandList *, ID3D12RootSignature *)>;
	void setRootSignature(std::shared_ptr<RootSignature> pRootSignature, const SetRootSignatureFunc &setFunc);
	void bindDescriptorHeaps();
	void setShouldReset(bool bReset);
	bool shouldReset() const;
	WRL::ComPtr<ID3D12Resource> copyTextureSubResource(WRL::ComPtr<ID3D12Resource> pDestResource,
		size_t firstSubResource, 
		size_t numSubResource, 
		D3D12_SUBRESOURCE_DATA *pSubResourceData
	);
	std::shared_ptr<Texture> createTextureImpl(const DX::TexMetadata &metadata, const DX::ScratchImage &scratchImage, size_t genMip);
	void trackObject(WRL::ComPtr<ID3D12Object> &&pObject);
	void trackResource(WRL::ComPtr<ID3D12Resource> &&pResource);
	void copyResource(WRL::ComPtr<ID3D12Resource> dstRes, WRL::ComPtr<ID3D12Resource> srcRes);
	void UAVBarrier(WRL::ComPtr<ID3D12Resource> pResource, bool flushBarriers);
	void generateMips_UAV(const std::shared_ptr<Texture> &pTexture, bool isSRGB);
private:
	bool								   _shouldReset = false;
	D3D12_COMMAND_LIST_TYPE                _cmdListType;
	std::weak_ptr<Device>                  _pDevice;
	WRL::ComPtr<ID3D12GraphicsCommandList> _pCommandList;
	WRL::ComPtr<ID3D12CommandAllocator>    _pCmdListAlloc;
	std::unique_ptr<ResourceStateTracker>  _pResourceStateTracker;
	std::unique_ptr<DynamicDescriptorHeap> _pDynamicDescriptorHeaps[kDynamicDescriptorHeapCount];
	ReadBackBufferPool                     _readBackBuffers;
	StaleResourcePool					   _staleResourceBuffers;
	StaleRawObjectPool					   _staleRawObjectBuffers;
	StaleRawResourcePool				   _staleRawResourceBuffers;
	RenderProfiler						   _renderProfiler;	
private:
	struct CommandListState {
		PSO           *pPSO;
		RootSignature *pRootSignature;
		VertexBuffer  *pVertexBuffers[kVertexBufferSlotCount];
		IResource     *pDepthStencil;
		IndexBuffer   *pIndexBuffer;
		D3D12_VIEWPORT viewport;
		D3D12_RECT	   scissorRect;
		bool           isSetViewport;
		bool           isSetScissorRect;
		UINT           stencilRef;
		D3D_PRIMITIVE_TOPOLOGY primitiveTopology = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
		ID3D12DescriptorHeap *pDescriptorHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
	public:
		CommandListState();
		bool debugCheckDraw() const;
		bool debugCheckDrawIndex() const;
		bool checkVertexBuffer() const;
	};
	CommandListState _currentGPUState;
};

}