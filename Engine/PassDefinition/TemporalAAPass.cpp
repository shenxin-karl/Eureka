#include "TemporalAAPass.h"
#include "EngineDefinition/EngineDefinition.h"
#include <DirectXColors.h>

#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "Dx12lib/Pipeline/RootSignature.h"
#include "ShaderHelper/ShaderHelper.h"

#include "EngineShaders/TAAResolveCS.h"
#include "EngineShaders/SharpenTAACS.h"

using namespace Math;

namespace Eureka {

enum TAAFlag {
	HAS_HISTORY_FLAG = (1 << 0),
};

struct alignas(16) CBData {
	float4		gResolution;         //width, height, 1/width, 1/height
	float2		gJitter;
	uint32_t	gFrameNumber;
	uint32_t	gDebugFlag;
};

TemporalAAPass::TemporalAAPass(const std::string &passName, dx12lib::IDirectContext &directCtx)
: ExecutablePass(passName)
, pScreenMap(this, "ScreenMap")
, pVelocityMap(this, "VelocityMap")
, pOutputMap(this, "OutputMap")
{
	auto pSharedDevice = directCtx.getDevice().lock();
	auto pRootSignature = pSharedDevice->createRootSignature(2, 8);
	pRootSignature->initStaticSampler(0, ShaderHelper::getStaticSamplers());
	pRootSignature->at(0).initAsConstants(dx12lib::RegisterSlot::CBV0, sizeof(CBData) / sizeof(float));
	pRootSignature->at(1).initAsDescriptorTable({
		{ dx12lib::RegisterSlot::SRV0, 3 }, // t0 t1
		{ dx12lib::RegisterSlot::UAV0, 1 },
	});
	pRootSignature->finalize();
	_pTemporalPipeline = pSharedDevice->createComputePSO("TemporalPipeline");

#if defined(DEBUG) || defined(_DEBUG)
	auto pBlob = ShaderHelper::compile(
		"EngineAssets/Shaders/TAAResolveCS.hlsl",
		nullptr, 
		"CS", 
		"cs_5_1"
	);
	_pTemporalPipeline->setComputeShader(pBlob);
#else
	_pTemporalPipeline->setComputeShader(g_TAAResolveCS, sizeof(g_TAAResolveCS));
#endif
	_pTemporalPipeline->setRootSignature(pRootSignature);
	_pTemporalPipeline->finalize();


	auto pSharpenRootSignature = pSharedDevice->createRootSignature(2, 8);
	pSharpenRootSignature->at(0).initAsConstants(dx12lib::RegisterSlot::CBV0, 5);
	pSharpenRootSignature->initStaticSampler(0, ShaderHelper::getStaticSamplers());
	pSharpenRootSignature->at(1).initAsDescriptorTable({
		{ dx12lib::RegisterSlot::SRV0, 1 }, 
		{ dx12lib::RegisterSlot::UAV0, 1 },
	});
	pSharpenRootSignature->finalize();

	_pSharpenPipeline = pSharedDevice->createComputePSO("SharpenPipeline");
#if defined(DEBUG) || defined(_DEBUG)
	auto pBlob1 = ShaderHelper::compile(
		"EngineAssets/Shaders/SharpenTAACS.hlsl",
		nullptr, 
		"CS", 
		"cs_5_1"
	);
	_pSharpenPipeline->setComputeShader(pBlob1);
#else
	_pSharpenPipeline->setComputeShader(g_SharpenTAACS, sizeof(g_SharpenTAACS));
#endif
	_pSharpenPipeline->setRootSignature(pSharpenRootSignature);
	_pSharpenPipeline->finalize();
}

void TemporalAAPass::execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) {
	ExecutablePass::execute(directCtx, view);

	uint64_t frameIndexMod2 = view.frameIndex % 2;
	uint64_t srcIdx = frameIndexMod2;
	uint64_t dstIdx = (~srcIdx) & 0x1;

	// TAA
	CBData data;
	data.gResolution.x = static_cast<float>(view.viewport.width);
	data.gResolution.y = static_cast<float>(view.viewport.height);
	data.gResolution.z = 1.f / view.viewport.width;
	data.gResolution.w = 1.f / view.viewport.height;
	data.gJitter.x = view.xJitter;
	data.gJitter.y = view.yJitter;
	data.gFrameNumber = static_cast<uint32_t>(view.frameIndex);
	data.gDebugFlag = 0;
	data.gDebugFlag |= (HAS_HISTORY_FLAG * _hasHistory);

	directCtx.beginEvent("Resolve");
	{
		directCtx.setComputePSO(_pTemporalPipeline);
		directCtx.setCompute32BitConstants(dx12lib::RegisterSlot::CBV0, sizeof(CBData) / sizeof(float), &data);
		directCtx.transitionBarrier(_pTemporalColor[dstIdx], D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
		directCtx.transitionBarrier(_pTemporalColor[srcIdx], D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
		directCtx.setUnorderedAccessView(StringName("gOutputMap"), _pTemporalColor[dstIdx]->get2dUAV());
		directCtx.setShaderResourceView(StringName("gTemporalMap"), _pTemporalColor[srcIdx]->get2dSRV());
		directCtx.setShaderResourceView(StringName("gScreenMap"), pScreenMap->get2dSRV());
		directCtx.setShaderResourceView(StringName("gVelocityMap"), pVelocityMap->get2dSRV());
		
		auto dispatchArgs = _pTemporalPipeline->calcDispatchArgs(view.viewport.width, view.viewport.height);
		directCtx.dispatch(dispatchArgs);
		
	}
	directCtx.endEvent();


	// Sharpen And copy
	directCtx.beginEvent("Sharpen");
	{
		directCtx.setComputePSO(_pSharpenPipeline);
		directCtx.transitionBarrier(_pTemporalColor[dstIdx], D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
		directCtx.setShaderResourceView(StringName("gTemporalColor"), _pTemporalColor[dstIdx]->get2dSRV());
		directCtx.setUnorderedAccessView(StringName("gOutputColorMap"), pOutputMap->get2dUAV());
		directCtx.setCompute32BitConstants(dx12lib::RegisterSlot::CBV0, 4, &data.gResolution);
		directCtx.setCompute32BitConstants(dx12lib::RegisterSlot::CBV0, 1, &sharpenFactor, 4);
		auto dispatchArgs = _pSharpenPipeline->calcDispatchArgs(view.viewport.width, view.viewport.height);
		directCtx.dispatch(dispatchArgs);
	}
	directCtx.endEvent();

	_hasHistory = true;
}

void TemporalAAPass::onResize(dx12lib::IDirectContext &directCtx, size_t width, size_t height) {
	ExecutablePass::onResize(directCtx, width, height);

	directCtx.trackResource(_pTemporalColor[0]);
	directCtx.trackResource(_pTemporalColor[1]);

	auto desc = dx12lib::Texture::make2D(
		kTemporalAAFormat, 
		width, 
		height, 
		D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET | D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS
	);

	D3D12_CLEAR_VALUE clearValue;
	clearValue.Format = kTemporalAAFormat;
	std::memcpy(&clearValue.Color, &DirectX::Colors::Black, sizeof(FLOAT) * 4);

	_pTemporalColor[0] = directCtx.createTexture(desc, &clearValue);
	_pTemporalColor[0]->setResourceName("TemporalColor0");
	_pTemporalColor[1] = directCtx.createTexture(desc, &clearValue);
	_pTemporalColor[1]->setResourceName("TemporalColor1");
}

}
