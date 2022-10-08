#pragma once
#include <Dx12lib/dx12libStd.h>
#include <memory>


namespace dx12lib {

class GenerateMipsPSO;
class GlobalResourceState;

struct DeviceInitDesc {
	DXGI_FORMAT backBufferFormat   = DXGI_FORMAT_UNKNOWN;
	DXGI_FORMAT depthStencilFormat = DXGI_FORMAT_UNKNOWN;
	size_t		fps				   = 120;
};

class Device : public NonCopyable, public std::enable_shared_from_this<Device> {
public:
	Device(std::shared_ptr<Adapter> pAdapter);
	Device(const Device &) = delete;
	Device &operator=(const Device &) = delete;
	~Device() override;
	void initialize(const DeviceInitDesc &desc);
	void destroy();
	std::shared_ptr<SwapChain> createSwapChain(HWND hwnd) const;
	std::shared_ptr<RootSignature> createRootSignature(size_t numRootParams, size_t numStaticSamplers = 0);
	std::shared_ptr<GraphicsPSO> createGraphicsPSO(const std::string &name);
	std::shared_ptr<ComputePSO> createComputePSO(const std::string &name);
	DescriptorAllocation allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE type, uint32 numDescriptors = 1);
	void releaseStaleDescriptor();
	const DeviceInitDesc &getDesc() const;
	std::shared_ptr<Adapter> getAdapter() const;
	std::shared_ptr<CommandQueue> getCommandQueue() const;
	ID3D12Device *getD3DDevice() const;
	GlobalResourceState *getGlobalResourceState() const;
	auto getGenerateMipsPSO() const -> std::shared_ptr<GenerateMipsPSO>;
private:
	WRL::ComPtr<ID3D12Device>            _pDevice;
	std::shared_ptr<Adapter>             _pAdapter;
	std::shared_ptr<CommandQueue>        _pCommandQueue;
	std::unique_ptr<DescriptorAllocator> _pDescriptorAllocators[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
	DeviceInitDesc				         _initDesc;
	std::unique_ptr<GlobalResourceState> _pGlobalResourceState;
	std::shared_ptr<GenerateMipsPSO>	 _pGenerateMipsPSO;
};

}