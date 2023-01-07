#include "GenerateMipsPSO.h"
#include "Dx12lib/Device/Device.h"
#include "Dx12lib/Pipeline/FXCShader.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "Dx12lib/Pipeline/RootSignature.h"

namespace dx12lib {

static unsigned char g_GenerateMips_CS_data[] = {
	#include "GenerateMips_CS.hlsl.h"
};

GenerateMipsPSO::GenerateMipsPSO(std::weak_ptr<Device> pDevice) {
	UINT compilesFlags = 0;
	#if defined(DEBUG) || defined(_DEBUG) 
		compilesFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	#endif

	_pComputeShader = std::make_shared<FXCShader>();

	CompileFormMemoryArgs compileArgs;
	compileArgs.filePath = "GenerateMips_CS.hlsl";
	compileArgs.target = "cs_5_1";
	compileArgs.entryPoint = "CS";
	compileArgs.pData = g_GenerateMips_CS_data;
	compileArgs.sizeInByte = sizeof(g_GenerateMips_CS_data);
	_pComputeShader->compileFormMemory(compileArgs);

	auto pSharedDevice = pDevice.lock();
	auto pRootSignature = pSharedDevice->createRootSignature(3, 1);
	pRootSignature->at(0).initAsConstants(RegisterSlot::CBV0, 6);
	pRootSignature->at(1).initAsDescriptorTable({ { RegisterSlot::SRV0, 1 } });
	pRootSignature->at(2).initAsDescriptorTable({ { RegisterSlot::UAV0, 4 } });
	CD3DX12_STATIC_SAMPLER_DESC sampler(
		0, D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP, D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP
	);
	pRootSignature->initStaticSampler(0, sampler);
	pRootSignature->finalize();

	_pPipelineState = pSharedDevice->createComputePSO("GenerateMipsPSO");
	_pPipelineState->setComputeShader(_pComputeShader);
	_pPipelineState->setRootSignature(pRootSignature);
	_pPipelineState->finalize();

	auto pd3dDevice = pSharedDevice->getD3DDevice();
	_defaultUAV = pSharedDevice->allocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 4);
	for (UINT i = 0; i < 4; ++i) {
		D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
		uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
		uavDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		uavDesc.Texture2D.MipSlice = i;
		uavDesc.Texture2D.PlaneSlice = 0;
		pd3dDevice->CreateUnorderedAccessView(
			nullptr, 
			nullptr, 
			&uavDesc, 
			_defaultUAV.getCPUHandle(i)
		);
	}
}

auto GenerateMipsPSO::getPipelineState() const -> std::shared_ptr<dx12lib::ComputePSO> {
	return _pPipelineState;
}

auto GenerateMipsPSO::getDefaultUVA(size_t i) const -> D3D12_CPU_DESCRIPTOR_HANDLE {
	return _defaultUAV.getCPUHandle(i);
}

}
