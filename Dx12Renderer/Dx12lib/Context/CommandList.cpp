#include <Dx12lib/Context/CommandList.h>
#include <Dx12lib/Device/Device.h>
#include <Dx12lib/Context/FrameResourceQueue.h>
#include <Dx12lib/Context/CommandQueue.h>
#include <Dx12lib/Resource/ResourceStateTracker.h>
#include <Dx12lib/Descriptor/DynamicDescriptorHeap.h>
#include <Dx12lib/Pipeline/PipelineStateObject.h>
#include <Dx12lib/Pipeline/RootSignature.h>
#include <Dx12lib/Tool/MakeObejctTool.hpp>
#include <Dx12lib/Tool/DDSTextureLoader.h>
#include <Dx12lib/Buffer/ReadBackBuffer.h>
#include <Dx12lib/Buffer/SRStructuredBuffer.h>
#include <Dx12lib/Buffer/FRSRStructuredBuffer.hpp>
#include <Dx12lib/Buffer/ConstantBuffer.h>
#include <Dx12lib/Buffer/IndexBuffer.h>
#include <Dx12lib/Buffer/VertexBuffer.h>
#include <Dx12lib/Texture/Texture.h>
#include <iostream>

#include "Dx12lib/Texture/GenerateMipsPSO.h"

#if defined(_DEBUG) || defined(DEBUG)
	#define DBG_CALL(f) f;
	#define DEBUG_MODE
#else
	#define DBG_CALL(f) nullptr;
#endif


template<typename T0, typename T1>
bool StateCMove(T0 &&dest, T1 &&src) {
	if (dest == src)
		return false;

	dest = src;
	return true;
}

namespace dx12lib {

/// private function
CommandList::CommandList(std::weak_ptr<FrameResourceItem> pFrameResourceItem) {
	auto pSharedFrameResourceItem = pFrameResourceItem.lock();
	_cmdListType = pSharedFrameResourceItem->getCommandListType();
	_pDevice = pSharedFrameResourceItem->getDevice();

	auto pDevice = pSharedFrameResourceItem->getDevice();
	auto pd3d12Device = pDevice.lock()->getD3DDevice();
	ThrowIfFailed(pd3d12Device->CreateCommandAllocator(
		_cmdListType,
		IID_PPV_ARGS(&_pCmdListAlloc)
	));
	ThrowIfFailed(pd3d12Device->CreateCommandList(
		0,
		_cmdListType,
		_pCmdListAlloc.Get(),
		nullptr,
		IID_PPV_ARGS(&_pCommandList)
	));

	_pResourceStateTracker = std::make_unique<dx12libTool::MakeResourceStateTracker>(_pDevice);
	for (std::size_t i = 0; i < kDynamicDescriptorHeapCount; ++i) {
		_pDynamicDescriptorHeaps[i] = std::make_unique<dx12libTool::MakeDynamicDescriptorHeap>(
			_pDevice,
			static_cast<D3D12_DESCRIPTOR_HEAP_TYPE>(i),
			static_cast<uint32>(kDynamicDescriptorPerHeap)
		);
	}
}

CommandList::~CommandList() {
}

/// ******************************************** Context api ***************************************************
ID3D12GraphicsCommandList *CommandList::getD3DCommandList() const noexcept {
	return _pCommandList.Get();
}

std::shared_ptr<CommandList> CommandList::getCommandList() noexcept {
	return shared_from_this();
}

void CommandList::trackResource(std::shared_ptr<IResource> &&pResource) {
	if (pResource == nullptr)
		return;
	_staleResourceBuffers.push_back(std::move(pResource));
}

std::weak_ptr<dx12lib::Device> CommandList::getDevice() const {
	return _pDevice;
}

/// ******************************************** CommonContext api ********************************************
std::shared_ptr<Texture> CommandList::createTextureFromFile(const std::wstring &fileName, bool sRGB, size_t genMip) {
	auto pos = fileName.find_last_of(L".");
	if (pos == std::wstring::npos) {
		assert(false);
		return nullptr;
	}

	namespace DX = DirectX;
	DX::TexMetadata  metadata{};
	DX::ScratchImage scratchImage;
	std::wstring extension = fileName.substr(pos);
	if (extension == L".dds")
		ThrowIfFailed(DX::LoadFromDDSFile(fileName.c_str(), DX::DDS_FLAGS_NONE, &metadata, scratchImage));
	else if (extension == L".hdr")
		ThrowIfFailed(DX::LoadFromHDRFile(fileName.c_str(), &metadata, scratchImage));
	else if (extension == L".tga")
		ThrowIfFailed(DX::LoadFromTGAFile(fileName.c_str(), &metadata, scratchImage));
	else
		ThrowIfFailed(DX::LoadFromWICFile(fileName.c_str(), DX::WIC_FLAGS_NONE, &metadata, scratchImage));
	if (sRGB)
		metadata.format = DX::MakeSRGB(metadata.format);
	
	auto pTex = createTextureImpl(metadata, scratchImage, genMip);
	pTex->getD3DResource()->SetName(fileName.c_str());
	return pTex;
}

std::shared_ptr<Texture> CommandList::createTextureFromMemory(const std::string &extension,
	const void *pData, 
	size_t sizeInByte,
	bool sRGB,
	size_t genMip)
{
	namespace DX = DirectX;
	DX::TexMetadata  metadata{};
	DX::ScratchImage scratchImage;
	if (extension == "dds")
		ThrowIfFailed(DX::LoadFromDDSMemory(pData, sizeInByte, DX::DDS_FLAGS_NONE, &metadata, scratchImage));
	else if (extension == "hdr")
		ThrowIfFailed(DX::LoadFromHDRMemory(pData, sizeInByte, &metadata, scratchImage));
	else if (extension == "tga")
		ThrowIfFailed(DX::LoadFromTGAMemory(pData, sizeInByte, &metadata, scratchImage));
	else
		ThrowIfFailed(DX::LoadFromWICMemory(pData, sizeInByte, DX::WIC_FLAGS_NONE, &metadata, scratchImage));
	if (sRGB)
		metadata.format = DX::MakeSRGB(metadata.format);
	return createTextureImpl(metadata, scratchImage, genMip);
}

void CommandList::setDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType,
                                    WRL::ComPtr<ID3D12DescriptorHeap> pHeap) {
	if (_currentGPUState.pDescriptorHeaps[heapType] != pHeap.Get()) {
		_currentGPUState.pDescriptorHeaps[heapType] = pHeap.Get();
		bindDescriptorHeaps();
	}
}

void CommandList::setConstantBufferView(const ShaderRegister &sr, const ConstantBufferView &cbv) {
	assert(_currentGPUState.pRootSignature != nullptr);
	assert(sr.slot.isCBV());
	assert(cbv.valid());
#ifdef DEBUG_MODE
	WRL::ComPtr<ID3D12Resource> pD3DResource = cbv.getResource()->getD3DResource();
	D3D12_RESOURCE_STATES state = _pResourceStateTracker->getResourceState(pD3DResource.Get());
	assert(cbv.getResource()->checkCBVState(state));
#endif
	_pDynamicDescriptorHeaps[0]->stageDescriptor(sr, cbv);
}

void CommandList::setConstantBufferView(const std::string &boundResourceName, const ConstantBufferView &cbv) {
	assert(cbv.valid());
	assert(cbv.valid());
	auto boundResource = _currentGPUState.pPSO->getBoundResource(boundResourceName);
	assert(boundResource != std::nullopt);
	assert(boundResource->viewType == D3D12_DESCRIPTOR_RANGE_TYPE_CBV);
	setConstantBufferView(boundResource->shaderRegister, cbv);
}

void CommandList::setShaderResourceView(const ShaderRegister &sr, const ShaderResourceView &srv) 
{
	assert(_currentGPUState.pRootSignature != nullptr);
	assert(sr.slot.isSRV());
	assert(srv.valid());
#ifdef DEBUG_MODE
	WRL::ComPtr<ID3D12Resource> pD3DResource = srv.getResource()->getD3DResource();
	D3D12_RESOURCE_STATES state = _pResourceStateTracker->getResourceState(pD3DResource.Get());
	assert(srv.getResource()->checkSRVState(state));
#endif
	_pDynamicDescriptorHeaps[0]->stageDescriptor(sr, srv);
}

void CommandList::setShaderResourceView(const std::string &boundResourceName,
	const ShaderResourceView &srv, 
	size_t offset, 
	size_t numDescriptors) 
{
	assert(srv.valid());
	auto boundResource = _currentGPUState.pPSO->getBoundResource(boundResourceName);
	assert(boundResource != std::nullopt);
	assert(boundResource->viewType == D3D12_DESCRIPTOR_RANGE_TYPE_SRV);
	assert((offset + numDescriptors) <= boundResource->count);
	ShaderRegister shaderRegister = boundResource->shaderRegister;
	shaderRegister += offset;

	assert(_currentGPUState.pRootSignature != nullptr);
#ifdef DEBUG_MODE
	WRL::ComPtr<ID3D12Resource> pD3DResource = srv.getResource()->getD3DResource();
	D3D12_RESOURCE_STATES state = _pResourceStateTracker->getResourceState(pD3DResource.Get());
	assert(srv.getResource()->checkSRVState(state));
#endif

	CD3DX12_CPU_DESCRIPTOR_HANDLE handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(srv.getCPUDescriptorHandle());
	UINT incrementSize = static_cast<UINT>(_pDynamicDescriptorHeaps[0]->getDescriptorHandleIncrementSize());
	for (size_t i = 0; i < numDescriptors; ++i) {
		_pDynamicDescriptorHeaps[0]->stageDescriptor(shaderRegister, handle);
		handle.Offset(1, incrementSize);
		shaderRegister += 1;
	}
}

void CommandList::readBack(std::shared_ptr<ReadBackBuffer> pReadBackBuffer) {
	assert(pReadBackBuffer != nullptr);
	pReadBackBuffer->setCompleted(false);
	_readBackBuffers.push_back(pReadBackBuffer);
}

void CommandList::copyResourceImpl(std::shared_ptr<IResource> pDest, std::shared_ptr<IResource> pSrc) {
	auto destDesc = pDest->getD3DResource()->GetDesc();
	auto srcDesc = pSrc->getD3DResource()->GetDesc();;
	assert(destDesc.Width == srcDesc.Width);
	assert(destDesc.Height == srcDesc.Height);
	assert(destDesc.Format == srcDesc.Format);
	transitionBarrier(pDest, D3D12_RESOURCE_STATE_COPY_DEST);
	transitionBarrier(pSrc, D3D12_RESOURCE_STATE_COPY_SOURCE);
	flushResourceBarriers();
	_pCommandList->CopyResource(
		pDest->getD3DResource().Get(),
		pSrc->getD3DResource().Get()
	);
}

void CommandList::transitionBarrierImpl(std::shared_ptr<IResource> pBuffer, 
	D3D12_RESOURCE_STATES state, 
	UINT subResource,
	bool flushBarrier) 
{
	_pResourceStateTracker->transitionResource(pBuffer->getD3DResource().Get(), state, subResource);
	if (flushBarrier)
		flushResourceBarriers();
}

void CommandList::aliasBarrierImpl(std::shared_ptr<IResource> pBefore,
	std::shared_ptr<IResource> pAfter, 
	bool flushBarrier) 
{
	_pResourceStateTracker->aliasBarrier(pBefore.get(), pAfter.get());
	if (flushBarrier)
		flushResourceBarriers();
}

void CommandList::flushResourceBarriers() {
	_pResourceStateTracker->flushResourceBarriers(this);
}

/// ******************************************** GraphicsContext api ********************************************
std::shared_ptr<VertexBuffer>
CommandList::createVertexBuffer(const void *pData, std::size_t numElements, std::size_t stride) {
	return std::make_shared<dx12libTool::MakeVertexBuffer>(_pDevice,
		shared_from_this(),
		pData,
		numElements,
		stride
	);
}

std::shared_ptr<IndexBuffer>
CommandList::createIndexBuffer(const void *pData, std::size_t numElements, DXGI_FORMAT indexFormat) {
	return std::make_shared<dx12libTool::MakeIndexBuffer>(_pDevice,
		shared_from_this(),
		pData,
		numElements,
		indexFormat
	);
}

void CommandList::setViewport(const D3D12_VIEWPORT &viewport) {
	if (std::memcmp(&viewport, &_currentGPUState.viewport, sizeof(D3D12_VIEWPORT)) == 0)
		return;

	_currentGPUState.isSetViewport = true;
	_currentGPUState.viewport = viewport;
	_pCommandList->RSSetViewports(1, &viewport);
}

void CommandList::setScissorRect(const D3D12_RECT &rect) {
	if (std::memcmp(&rect, &_currentGPUState.scissorRect, sizeof(D3D12_RECT)) == 0)
		return;

	_currentGPUState.isSetScissorRect = true;
	_currentGPUState.scissorRect = rect;
	_pCommandList->RSSetScissorRects(1, &rect);
}

void CommandList::setVertexBuffer(const std::shared_ptr<VertexBuffer> &pVertBuffer, UINT slot /*= 0 */) {
	assert(pVertBuffer != nullptr);
	assert(slot < kVertexBufferSlotCount);
	assert(_currentGPUState.pPSO != nullptr);
	if (StateCMove(_currentGPUState.pVertexBuffers[slot], pVertBuffer.get())) {
		_pCommandList->IASetVertexBuffers(
			slot,
			1,
			RVPtr(pVertBuffer->getVertexBufferView())
		);
	}
}

void CommandList::setIndexBuffer(const std::shared_ptr<IndexBuffer> &pIndexBuffer) {
	assert(pIndexBuffer != nullptr);
	assert(_currentGPUState.pPSO != nullptr);
	if (StateCMove(_currentGPUState.pIndexBuffer, pIndexBuffer.get()))
		_pCommandList->IASetIndexBuffer(RVPtr(pIndexBuffer->getIndexBufferView()));
}


void CommandList::setGraphicsPSO(std::shared_ptr<GraphicsPSO> pPipelineStateObject) {
	assert(pPipelineStateObject != nullptr);
	assert(!pPipelineStateObject->isDirty());
	if (StateCMove(_currentGPUState.pPSO, pPipelineStateObject.get())) {
		setGraphicsRootSignature(pPipelineStateObject->getRootSignature());
		_pCommandList->SetPipelineState(pPipelineStateObject->getPipelineStateObject().Get());
	}
}

void CommandList::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology) {
	if (_currentGPUState.primitiveTopology != topology) {
		_currentGPUState.primitiveTopology = topology;
		_pCommandList->IASetPrimitiveTopology(topology);
	}
}

void CommandList::setStencilRef(UINT stencilRef) {
	if (stencilRef != _currentGPUState.stencilRef) {
		_currentGPUState.stencilRef = stencilRef;
		_pCommandList->OMSetStencilRef(stencilRef);
	}
}

void CommandList::setGraphics32BitConstants(const ShaderRegister &sr, size_t numConstants, const void *pData, size_t destOffset) {
	auto location = _currentGPUState.pRootSignature->getShaderParamLocation(sr);
	if (!location.has_value()) {
		assert(location.has_value());
		return;
	}
	assert(destOffset + numConstants <= location->num32BitValues);
	_pCommandList->SetGraphicsRoot32BitConstants(
		static_cast<UINT>(location->rootParamIndex),
		static_cast<UINT>(numConstants), 
		pData,
		static_cast<UINT>(destOffset)
	);
}

void CommandList::setRenderTarget(const RenderTargetView &rtv, const DepthStencilView &dsv) {
	assert(rtv.valid());
	assert(dsv.valid());
	_pCommandList->OMSetRenderTargets(
		1, 
		RVPtr(rtv.getCPUDescriptorHandle()), 
		false, 
		RVPtr(dsv.getCPUDescriptorHandle())
	);
}

void CommandList::setRenderTarget(const RenderTargetView &rtv) {
	assert(rtv.valid());
	_pCommandList->OMSetRenderTargets(
		1,
		RVPtr(rtv.getCPUDescriptorHandle()),
		false,
		nullptr
	);
}

void CommandList::setRenderTarget(const DepthStencilView &dsv) {
	assert(dsv.valid());
	_pCommandList->OMSetRenderTargets(
		0,
		nullptr,
		false,
		RVPtr(dsv.getCPUDescriptorHandle())
	);
}

void CommandList::setRenderTargets(const std::vector<RenderTargetView> &rtvs, const DepthStencilView &dsv) {
	assert(dsv.valid());
	for (auto &view : rtvs)
		assert(view.valid());

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> handles(rtvs.begin(), rtvs.end());
	_pCommandList->OMSetRenderTargets(
		static_cast<UINT>(rtvs.size()),
		handles.data(),
		false,
		RVPtr(dsv.getCPUDescriptorHandle())
	);
}

void CommandList::drawInstanced(size_t vertCount,
                                size_t instanceCount,
                                size_t baseVertexLocation,
                                size_t startInstanceLocation)
{
	assert(_currentGPUState.debugCheckDraw());
	flushResourceBarriers();
	for (auto &pDynamicHeap : _pDynamicDescriptorHeaps)
		pDynamicHeap->commitStagedDescriptorForDraw(this);
	_pCommandList->DrawInstanced(
		static_cast<UINT>(vertCount), 
		static_cast<UINT>(instanceCount),
		static_cast<UINT>(baseVertexLocation),
		static_cast<UINT>(startInstanceLocation)
	);
}

void CommandList::drawIndexedInstanced(size_t indexCountPerInstance,
	size_t instanceCount,
	size_t startIndexLocation,
	size_t baseVertexLocation,
	size_t startInstanceLocation)
{
	assert(_currentGPUState.debugCheckDrawIndex());
	flushResourceBarriers();
	for (auto &pDynamicHeap : _pDynamicDescriptorHeaps)
		pDynamicHeap->commitStagedDescriptorForDraw(this);
	_pCommandList->DrawIndexedInstanced(
		static_cast<UINT>(indexCountPerInstance), 
		static_cast<UINT>(instanceCount), 
		static_cast<UINT>(startIndexLocation),
		static_cast<UINT>(baseVertexLocation),
		static_cast<UINT>(startIndexLocation)
	);
}

void CommandList::clearColor(const RenderTargetView &rtv, Math::float4 color) {
	_pCommandList->ClearRenderTargetView(
		rtv,
		reinterpret_cast<FLOAT *>(&color),
		0,
		nullptr
	);
}

void CommandList::clearColor(const RenderTargetView &rtv, const float colors[4]) {
	_pCommandList->ClearRenderTargetView(
		rtv,
		colors,
		0,
		nullptr
	);
}

void CommandList::clearDepth(const DepthStencilView &dsv, float depth) {
	_pCommandList->ClearDepthStencilView(
		dsv,
		D3D12_CLEAR_FLAG_DEPTH,
		depth,
		1,
		0,
		nullptr
	);
}

void CommandList::clearStencil(const DepthStencilView &dsv, UINT stencil) {
	_pCommandList->ClearDepthStencilView(
		dsv,
		D3D12_CLEAR_FLAG_STENCIL,
		1.f,
		stencil,
		0,
		nullptr
	);
}

void CommandList::clearDepthStencil(const DepthStencilView &dsv, float depth, UINT stencil) {
	_pCommandList->ClearDepthStencilView(
		dsv,
		D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
		depth,
		stencil,
		0,
		nullptr
	);
}


/// ******************************************** ComputeContext api ********************************************

void CommandList::setComputePSO(std::shared_ptr<ComputePSO> pPipelineStateObject) {
	assert(pPipelineStateObject != nullptr);
	assert(!pPipelineStateObject->isDirty());
	if (StateCMove(_currentGPUState.pPSO, pPipelineStateObject.get())) {
		setComputeRootSignature(pPipelineStateObject->getRootSignature());
		_pCommandList->SetPipelineState(pPipelineStateObject->getPipelineStateObject().Get());
	}
}

void CommandList::setUnorderedAccessView(const ShaderRegister &sr, const UnorderedAccessView &uav) {
	assert(_currentGPUState.pRootSignature != nullptr);
	assert(uav.valid());
#ifdef DEBUG_MODE
	WRL::ComPtr<ID3D12Resource> pD3DResource = uav.getResource()->getD3DResource();
	D3D12_RESOURCE_STATES state = _pResourceStateTracker->getResourceState(pD3DResource.Get());
	assert(uav.getResource()->checkUAVState(state));
#endif
	_pDynamicDescriptorHeaps[0]->stageDescriptor(sr, uav);
}

void CommandList::setCompute32BitConstants(const ShaderRegister &sr, size_t numConstants, const void *pData, size_t destOffset) {
	auto location = _currentGPUState.pRootSignature->getShaderParamLocation(sr);
	if (!location.has_value()) {
		assert(false);
		return;	
	}
	assert(destOffset + numConstants <= location->offset);
	_pCommandList->SetComputeRoot32BitConstants(
		static_cast<UINT>(location->rootParamIndex),
		static_cast<UINT>(numConstants),
		pData, 
		static_cast<UINT>(destOffset));
}

void CommandList::generateMips(std::shared_ptr<Texture> pTexture) {
	if (pTexture == nullptr)
		return;

	auto pD3d12Resource = pTexture->getD3DResource();
	if (pD3d12Resource == nullptr)
		return;

	const auto &resourceDesc = pTexture->getDesc();
	if (resourceDesc.Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE2D && resourceDesc.DepthOrArraySize != 1) {
		assert(false);
		return;
	}

	if (resourceDesc.MipLevels == 1)
		return;

	auto pShardDevice = _pDevice.lock();
	auto pD3d12Device = pShardDevice->getD3DDevice();
	WRL::ComPtr<ID3D12Resource> pd3dUAVResource = pD3d12Resource;
	WRL::ComPtr<ID3D12Resource> pd3dAliasResource;

	// 如果传入的资源不允许 UAV 访问
	// 创建一个堆, 堆的同一个位置上创建两个资源, pD3DAliasResource 和需要生成 mipmap 的资源格式相同
	// pD3DUAVResource 和原来的资源格式相同. 但是支持 UAV 访问, 使用 pD3DUAVResource 生成 mipmap. 因为是相同位置,
	// 所以 pD3DAliasResource 的内容已经改变, 拷贝回到 需要生成 mipmap 的资源上即可
	if (!pTexture->checkUAVSupport() || (resourceDesc.Flags & D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS) == 0) {
		// Describe an alias resource that is used to copy the original texture.
		auto aliasDesc = resourceDesc;
		// Placed resources can't be render targets or depth-stencil views.
		aliasDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
		aliasDesc.Flags &= ~(D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET | D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);
		// Describe a UAV compatible resource that is used to perform
		// mipmapping of the original texture.
		auto uavDesc = aliasDesc;  // The flags for the UAV description must match that of the alias description.
		uavDesc.Format = getUAVCompatableFormat(resourceDesc.Format);
		D3D12_RESOURCE_DESC resourceDescs[] = { aliasDesc, uavDesc };
		// 创建一个足够大的堆, 以存储原始资源的副本. 
		auto allocationInfo = pD3d12Device->GetResourceAllocationInfo(
			0, 
			_countof(resourceDescs), 
			resourceDescs
		);

		D3D12_HEAP_DESC heapDesc = {};
		heapDesc.SizeInBytes = allocationInfo.SizeInBytes;
		heapDesc.Alignment = allocationInfo.Alignment;
		heapDesc.Flags = D3D12_HEAP_FLAG_ALLOW_ONLY_NON_RT_DS_TEXTURES;
		heapDesc.Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapDesc.Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapDesc.Properties.Type = D3D12_HEAP_TYPE_DEFAULT;

		WRL::ComPtr<ID3D12Heap> heap;
		ThrowIfFailed(pD3d12Device->CreateHeap(&heapDesc, IID_PPV_ARGS(&heap)));
		//确保堆在命令列表之前不会超出作用域 在命令队列上执行完毕. 
		//创建一个符合原始资源. 此资源用于复制原始文件, 纹理 UAV 兼容的资源. 
		ThrowIfFailed(pD3d12Device->CreatePlacedResource(
			heap.Get(), 
			0, 
			&aliasDesc, 
			D3D12_RESOURCE_STATE_COMMON,
			nullptr, 
			IID_PPV_ARGS(&pd3dAliasResource)
		));

		pShardDevice->getGlobalResourceState()->addGlobalResourceState(
			pd3dAliasResource.Get(), 
			D3D12_RESOURCE_STATE_COMMON
		);

		// 在与 alias 资源相同的堆中创建一个UAV兼容的资源. 
		ThrowIfFailed(pD3d12Device->CreatePlacedResource(
			heap.Get(), 
			0, 
			&uavDesc, 
			D3D12_RESOURCE_STATE_COMMON, 
			nullptr,
			IID_PPV_ARGS(&pd3dUAVResource)
		));

		pShardDevice->getGlobalResourceState()->addGlobalResourceState(
			pd3dUAVResource.Get(), 
			D3D12_RESOURCE_STATE_COMMON
		);

		// Add an aliasing barrier for the alias resource.
		_pResourceStateTracker->aliasBarrier(nullptr, pd3dAliasResource.Get());

		// Copy the original resource to the alias resource.
		// This ensures GPU validation.
		copyResource(pd3dAliasResource, pD3d12Resource);
		trackObject(std::move(heap));

		// Add an aliasing barrier for the UAV compatible resource.
		_pResourceStateTracker->aliasBarrier(pd3dAliasResource.Get(), pd3dUAVResource.Get());
	}

	auto pUAVTexture = createTexture(pd3dUAVResource);
	generateMips_UAV(pUAVTexture, isSRGBFormat(resourceDesc.Format));
	trackResource(pUAVTexture);

	if (pd3dAliasResource != nullptr) {
		_pResourceStateTracker->aliasBarrier(pd3dUAVResource.Get(), pd3dAliasResource.Get());
		copyResource(pD3d12Resource, pd3dAliasResource);
		trackResource(std::move(pd3dAliasResource));
		trackResource(std::move(pd3dUAVResource));
	}
}

void CommandList::dispatch(size_t GroupCountX, size_t GroupCountY, size_t GroupCountZ) {
	assert(GroupCountX >= 1);
	assert(GroupCountY >= 1);
	assert(GroupCountZ >= 1);
	flushResourceBarriers();
	for (auto &pDynamicHeap : _pDynamicDescriptorHeaps)
		pDynamicHeap->commitStagedDescriptorForDispatch(this);
	_pCommandList->Dispatch(
		static_cast<UINT>(GroupCountX), 
		static_cast<UINT>(GroupCountY), 
		static_cast<UINT>(GroupCountZ)
	);
}

void CommandList::UAVBarrier(const std::shared_ptr<IResource> &pResource, bool flushBarriers) {
	UAVBarrier(pResource->getD3DResource(), flushBarriers);
}

void CommandList::setGraphicsRootSignature(std::shared_ptr<RootSignature> pRootSignature) {
	setRootSignature(pRootSignature, &ID3D12GraphicsCommandList::SetGraphicsRootSignature);
}

void CommandList::setComputeRootSignature(std::shared_ptr<RootSignature> pRootSignature) {
	setRootSignature(pRootSignature, &ID3D12GraphicsCommandList::SetComputeRootSignature);
}

void CommandList::close() {
	flushResourceBarriers();
	setShouldReset(true);
	ThrowIfFailed(_pCommandList->Close());
}

void CommandList::close(std::shared_ptr<CommandList> pPendingCmdList) {
	_pResourceStateTracker->flushPendingResourceBarriers(pPendingCmdList);
	flushResourceBarriers();
	_pResourceStateTracker->commitFinalResourceStates();
	setShouldReset(true);
	ThrowIfFailed(_pCommandList->Close());
}

void CommandList::reset() {
	setShouldReset(false);
	_pCmdListAlloc->Reset();
	ThrowIfFailed(_pCommandList->Reset(_pCmdListAlloc.Get(), nullptr));
	_pResourceStateTracker->reset();

	std::memset(&_currentGPUState, 0, sizeof(_currentGPUState));
	for (auto &pDynamicDescriptorHeap : _pDynamicDescriptorHeaps)
		pDynamicDescriptorHeap->reset();

	for (auto &pReadBackBuffer : _readBackBuffers)
		pReadBackBuffer->setCompleted(true);

	_readBackBuffers.clear();
	_staleResourceBuffers.clear();
	_staleRawObjectBuffers.clear();

	auto pGlobalResourceState = _pDevice.lock()->getGlobalResourceState();
	for (auto &pResource : _staleRawResourceBuffers) 
		pGlobalResourceState->removeGlobalResourceState(pResource.Get());
	_staleRawResourceBuffers.clear();
}

void CommandList::setRootSignature(std::shared_ptr<RootSignature> pRootSignature, 
	const SetRootSignatureFunc &setFunc) 
{
	if (_currentGPUState.pRootSignature != pRootSignature.get()) {
		_currentGPUState.pRootSignature = pRootSignature.get();
		setFunc(_pCommandList.Get(), pRootSignature->getRootSignature().Get());
		for (auto &pHeap : _pDynamicDescriptorHeaps)
			pHeap->parseRootSignature(pRootSignature);
	}
}

void CommandList::bindDescriptorHeaps() {
	UINT numDescriptors = 0;
	ID3D12DescriptorHeap *pHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES] = { nullptr };
	for (std::size_t i = 0; i < D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES; ++i) {
		if (auto *pHeap = _currentGPUState.pDescriptorHeaps[i]) {
			pHeaps[numDescriptors] = pHeap;
			++numDescriptors;
		}
	}
	if (numDescriptors > 0)
		_pCommandList->SetDescriptorHeaps(numDescriptors, pHeaps);
}

void CommandList::setShouldReset(bool bReset) {
	_shouldReset = bReset;
}

bool CommandList::shouldReset() const {
	return _shouldReset;
}

WRL::ComPtr<ID3D12Resource> CommandList::copyTextureSubResource(WRL::ComPtr<ID3D12Resource> pDestResource, 
	size_t firstSubResource,
	size_t numSubResource, 
	D3D12_SUBRESOURCE_DATA *pSubResourceData)
{
	if (pDestResource == nullptr) 
		return nullptr;

	_pResourceStateTracker->transitionResource(pDestResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST);

	size_t requiredSize = GetRequiredIntermediateSize(
		pDestResource.Get(), 
		static_cast<UINT>(firstSubResource),
		static_cast<UINT>(numSubResource)
	);
	WRL::ComPtr<ID3D12Resource> pSrcResource;
	ThrowIfFailed(_pDevice.lock()->getD3DDevice()->CreateCommittedResource(
		RVPtr(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD)),
		D3D12_HEAP_FLAG_NONE,
		RVPtr(CD3DX12_RESOURCE_DESC::Buffer(requiredSize)),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&pSrcResource)
	));

	UpdateSubresources(_pCommandList.Get(), 
		pDestResource.Get(), 
		pSrcResource.Get(),
		0,
		static_cast<UINT>(firstSubResource),
		static_cast<UINT>(numSubResource),
		pSubResourceData
	);

	return pSrcResource;
}

std::shared_ptr<Texture> CommandList::createTextureImpl(const DX::TexMetadata &metadata, 
	const DX::ScratchImage &scratchImage, 
	size_t genMip)
{
	size_t resolution = std::max(metadata.width, metadata.height);
	DWORD maxMipMapLevel;
	_BitScanForward(&maxMipMapLevel, static_cast<DWORD>(resolution));
	maxMipMapLevel += 1;

	UINT16 mapLevels = std::max(
		static_cast<UINT16>(metadata.mipLevels),
		std::min(static_cast<UINT16>(maxMipMapLevel), static_cast<UINT16>(genMip))
	);

	D3D12_RESOURCE_DESC textureDesc{};
	switch (metadata.dimension) {
	case DX::TEX_DIMENSION_TEXTURE2D:
		textureDesc = CD3DX12_RESOURCE_DESC::Tex2D(
			metadata.format,
			static_cast<UINT64>(metadata.width),
			static_cast<UINT>(metadata.height),
			static_cast<UINT16>(metadata.arraySize),
			mapLevels
		);
		break;
	case DX::TEX_DIMENSION_TEXTURE1D:
	case DX::TEX_DIMENSION_TEXTURE3D:
	default:
		assert(false);
		return nullptr;
	}

	auto pSharedDevice = getDevice().lock();
	WRL::ComPtr<ID3D12Resource> pTextureResource;
	ThrowIfFailed(pSharedDevice->getD3DDevice()->CreateCommittedResource(
		RVPtr(CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT)),
		D3D12_HEAP_FLAG_NONE,
		&textureDesc,
		D3D12_RESOURCE_STATE_COMMON,
		nullptr,
		IID_PPV_ARGS(&pTextureResource)
	));
	auto pGlobalResourceState = _pDevice.lock()->getGlobalResourceState();
	pGlobalResourceState->addGlobalResourceState(pTextureResource.Get(), D3D12_RESOURCE_STATE_COMMON);

	std::vector<D3D12_SUBRESOURCE_DATA> subResources{ scratchImage.GetImageCount() };
	const DX::Image *pImages = scratchImage.GetImages();
	for (size_t i = 0; i < scratchImage.GetImageCount(); ++i) {
		auto &subResource = subResources[i];
		subResource.RowPitch = pImages[i].rowPitch;
		subResource.SlicePitch = pImages[i].slicePitch;
		subResource.pData = pImages[i].pixels;
	}


	auto pUploader = copyTextureSubResource(pTextureResource,
		0,
		subResources.size(),
		subResources.data()
	);

	trackObject(std::move(pUploader));

	std::shared_ptr<dx12lib::Texture> pTexture = nullptr;
	switch (metadata.dimension) {
	case DirectX::TEX_DIMENSION_TEXTURE2D:
		pTexture = std::make_shared<dx12libTool::MakeTexture>(_pDevice, pTextureResource);
		break;
	case DirectX::TEX_DIMENSION_TEXTURE3D:
	case DirectX::TEX_DIMENSION_TEXTURE1D:
	default:
		assert(false);
	}

	if (pTexture != nullptr && metadata.mipLevels < mapLevels)
		generateMips(pTexture);

	transitionBarrier(pTexture, D3D12_RESOURCE_STATE_GENERIC_READ);
	return pTexture;
}

void CommandList::trackObject(WRL::ComPtr<ID3D12Object> &&pObject) {
	if (pObject != nullptr)
		_staleRawObjectBuffers.push_back(std::move(pObject));
}

void CommandList::trackResource(WRL::ComPtr<ID3D12Resource> &&pResource) {
	if (pResource != nullptr)
		_staleRawResourceBuffers.push_back(std::move(pResource));
}

void CommandList::copyResource(WRL::ComPtr<ID3D12Resource> dstRes, WRL::ComPtr<ID3D12Resource> srcRes) {
	assert(dstRes);
	assert(srcRes);

	_pResourceStateTracker->transitionResource(dstRes.Get(), D3D12_RESOURCE_STATE_COPY_DEST);
	_pResourceStateTracker->transitionResource(srcRes.Get(), D3D12_RESOURCE_STATE_COPY_SOURCE);
	flushResourceBarriers();
	_pCommandList->CopyResource(dstRes.Get(), srcRes.Get());
}

void CommandList::UAVBarrier(WRL::ComPtr<ID3D12Resource> pResource, bool flushBarriers) {
	auto barrier = CD3DX12_RESOURCE_BARRIER::UAV(pResource.Get());
	_pResourceStateTracker->resourceBarrier(barrier);
	if (flushBarriers)
		flushResourceBarriers();
}

void CommandList::generateMips_UAV(const std::shared_ptr<Texture> &pTexture, bool isSRGB) {
	auto pGenerateMipsPSO = _pDevice.lock()->getGenerateMipsPSO();

	GenerateMipsCB generateMipsCb;
	generateMipsCb.IsSRGB = isSRGB;
	const auto &resourceDesc = pTexture->getDesc();
	setComputePSO(pGenerateMipsPSO->getPipelineState());

	for (size_t srcMip = 0; srcMip < resourceDesc.MipLevels-1; ) {
		uint64_t srcWidth = resourceDesc.Width >> srcMip;
		uint32_t srcHeight = resourceDesc.Height >> srcMip;
		uint32_t dstWidth = static_cast<uint32_t>(srcWidth >> 1);
		uint32_t dstHeight = srcHeight >> 1;

		// 0b00(0): Both width and height are even.
		// 0b01(1): Width is odd, height is even.
		// 0b10(2): Width is even, height is odd.
		// 0b11(3): Both width and height are odd.
		 generateMipsCb.SrcDimension = (srcHeight & 1) << 1 | (srcWidth & 1);

		DWORD mipCount;
		auto mask = (dstWidth == 1 ? dstHeight : dstWidth) | (dstHeight == 1 ? dstWidth : dstHeight);
		_BitScanForward(&mipCount, mask);
		mipCount = std::min<DWORD>(4, mipCount + 1);
		mipCount = static_cast<DWORD>((srcMip + mipCount) >= resourceDesc.MipLevels ? resourceDesc.MipLevels - srcMip : mipCount);
		dstWidth = std::max<DWORD>(1, dstWidth);
		dstHeight = std::max<DWORD>(1, dstHeight);

		generateMipsCb.SrcMipLevel = static_cast<uint32_t>(srcMip);
		generateMipsCb.NumMipLevels = mipCount;
		generateMipsCb.TexelSize.x = 1.0f / static_cast<float>(dstWidth);
		generateMipsCb.TexelSize.y = 1.0f / static_cast<float>(dstHeight);
		setCompute32BitConstants(
			RegisterSlot::CBV0,
			6,
			&generateMipsCb,
			0
		);

		UINT subResourceIndex = static_cast<UINT>(srcMip);
		transitionBarrier(pTexture, D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE, subResourceIndex);
		_pDynamicDescriptorHeaps[0]->stageDescriptor(RegisterSlot::SRV0, pTexture->get2dSRV(0));
		ShaderRegister sr = RegisterSlot::UAV0;
		for (size_t mip = 0; mip < mipCount; ++mip) {
			auto uav = pTexture->get2dUAV(srcMip + mip + 1);
			transitionBarrier(pTexture, 
				D3D12_RESOURCE_STATE_UNORDERED_ACCESS, 
				static_cast<UINT>(subResourceIndex + mip + 1)
			);
			_pDynamicDescriptorHeaps[0]->stageDescriptor(sr + mip, uav);
		}
		for (size_t mip = mipCount; mip < 4; ++mip) 
			_pDynamicDescriptorHeaps[0]->stageDescriptor(sr + mip, pGenerateMipsPSO->getDefaultUVA(mip));

		UINT groupX = ((dstWidth + 8 - 1) / 8);
		UINT groupY = ((dstHeight + 8 - 1) / 8);
		dispatch(groupX, groupY, 1);

		UAVBarrier(pTexture, false);
		srcMip += mipCount;
	}

}

#define CheckState(ret, message)			\
do {										\
	if (!(ret)) {							\
		std::cerr << message << std::endl;	\
		assert(false);						\
		return false;						\
	}										\
} while (false)

	CommandList::CommandListState::CommandListState() {
		std::memset(this, 0, sizeof(*this));
	}

bool CommandList::CommandListState::debugCheckDraw() const {
	CheckState(pPSO != nullptr, "PipelineStateObject not set");
	CheckState(dynamic_cast<GraphicsPSO *>(pPSO), "PipelineStateObject cast to GraphicsPSO failed!");
	CheckState(pRootSignature != nullptr, "RootSignature not set");
	CheckState(isSetViewport, "Viewprot not set");
	CheckState(isSetScissorRect, "ScissorRect not set");
	CheckState(checkVertexBuffer(), "No bound vertex buffer");
	CheckState(primitiveTopology != D3D_PRIMITIVE_TOPOLOGY_UNDEFINED, "unknow primitive topology");
	return true;
}

bool CommandList::CommandListState::debugCheckDrawIndex() const {
	if (!debugCheckDraw())
		return false;

	CheckState(pIndexBuffer != nullptr, "No bound index buffer");
	return true;
}
#undef CheckState

bool CommandList::CommandListState::checkVertexBuffer() const {
	for (auto *pVertexBuffer : pVertexBuffers) {
		if (pVertexBuffers != nullptr)
			return true;
	}
	return false;
}

}