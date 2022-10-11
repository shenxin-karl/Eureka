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
	std::weak_ptr<Device> getDevice() const override;
	ID3D12GraphicsCommandList *getD3DCommandList() const noexcept override;
	std::shared_ptr<CommandList> getCommandList() noexcept override;
	const RenderProfiler &getRenderProfiler() const noexcept override;

/// CommonContext api
	void trackResource(std::shared_ptr<IResource> &&pResource) override;
	std::shared_ptr<Texture> createTextureFromFile(const std::wstring &fileName, bool sRGB, size_t genMip) override;
	std::shared_ptr<Texture> createTextureFromMemory(const std::string &extension, const void *pData, size_t sizeInByte, bool sRGB, size_t genMip) override;

	void setDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, WRL::ComPtr<ID3D12DescriptorHeap> pHeap) override;
	void setConstantBufferView(const ShaderRegister &sr, const ConstantBufferView &cbv) override;
	void setConstantBufferView(const std::string &boundResourceName, const ConstantBufferView &cbv) override;
	void setShaderResourceView(const ShaderRegister &sr, const ShaderResourceView &srv) override;
	void setShaderResourceView(const std::string &boundResourceName, const ShaderResourceView &srv, size_t offset, size_t numDescriptors) override;
	void readBack(std::shared_ptr<ReadBackBuffer> pReadBackBuffer) override;

	void copyResourceImpl(std::shared_ptr<IResource> pDest, std::shared_ptr<IResource> pSrc) override;
	void transitionBarrierImpl(std::shared_ptr<IResource> pBuffer, D3D12_RESOURCE_STATES state, UINT subResource, bool flushBarrier) override;
	void aliasBarrierImpl(std::shared_ptr<IResource> pBefore, std::shared_ptr<IResource> pAfter, bool flushBarrier) override;
	void flushResourceBarriers() override;

/// GraphicsContext api
	std::shared_ptr<VertexBuffer> createVertexBuffer(const void *pData, size_t numElements, size_t stride) override;
	std::shared_ptr<IndexBuffer> createIndexBuffer(const void *pData, size_t numElements, DXGI_FORMAT indexFormat) override;

	void setViewport(const D3D12_VIEWPORT &viewport) override;
	void setScissorRect(const D3D12_RECT &rect) override;
	void setVertexBuffer(const std::shared_ptr<VertexBuffer> &pVertBuffer, UINT slot) override;
	void setIndexBuffer(const std::shared_ptr<IndexBuffer> &pIndexBuffer) override;
	void setGraphicsPSO(std::shared_ptr<GraphicsPSO> pPipelineStateObject) override;
	void setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology) override;
	void setStencilRef(UINT stencilRef) override;
	void setGraphics32BitConstants(const ShaderRegister &sr, size_t numConstants, const void *pData, size_t destOffset) override;
	void setRenderTarget(const RenderTargetView &rtv, const DepthStencilView &dsv) override;
	void setRenderTarget(const RenderTargetView &rtv) override;
	void setRenderTarget(const DepthStencilView &dsv) override;
	void setRenderTargets(const std::vector<RenderTargetView> &rtvs, const DepthStencilView &dsv) override;

	void drawInstanced(size_t vertCount, size_t instanceCount, size_t baseVertexLocation, size_t startInstanceLocation) override;
	void drawIndexedInstanced(size_t indexCountPerInstance, size_t instanceCount, size_t startIndexLocation, size_t baseVertexLocation, size_t startInstanceLocation) override;

	void clearColor(const RenderTargetView &rtv, Math::float4 color) override;
	void clearColor(const RenderTargetView &rtv, const float colors[4]) override;
	void clearDepth(const DepthStencilView &dsv, float depth) override;
	void clearStencil(const DepthStencilView &dsv, UINT stencil) override;
	void clearDepthStencil(const DepthStencilView &dsv, float depth, UINT stencil) override;
/// ComputeContext api 
	void setComputePSO(std::shared_ptr<ComputePSO> pPipelineStateObject) override;
	void setUnorderedAccessView(const ShaderRegister &sr, const UnorderedAccessView &uav) override;
	void setUnorderedAccessView(const std::string &boundResourceName, const UnorderedAccessView &uav, size_t offset = 0, size_t numDescriptors = 1) override;
	void setCompute32BitConstants(const ShaderRegister &sr, size_t numConstants, const void *pData, size_t destOffset) override;
	void generateMips(std::shared_ptr<Texture> pTexture) override;
	void dispatch(size_t GroupCountX, size_t GroupCountY, size_t GroupCountZ) override;
	void UAVBarrier(const std::shared_ptr<IResource> &pResource, bool flushBarriers) override;

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