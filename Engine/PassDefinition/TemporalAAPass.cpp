#include "TemporalAAPass.h"
#include "EngineDefinition/EngineDefinition.h"
#include <DirectXColors.h>

#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "Dx12lib/Pipeline/RootSignature.h"
#include "EngineShaders/TAAResolveCS.h"
#include "ShaderHelper/ShaderHelper.h"

using namespace Math;

namespace Eureka {

struct alignas(16) CBData {
	float4		gResolution;         //width, height, 1/width, 1/height
	float2		gJitter;
	uint32_t	gFrameNumber;
	uint32_t	padding0;
};

TemporalAAPass::TemporalAAPass(const std::string &passName, dx12lib::IDirectContext &directCtx)
: ExecutablePass(passName)
, pScreenMap(this, "ScreenMap")
, pOutputMap(this, "OutputMap")
{
	auto pSharedDevice = directCtx.getDevice().lock();
	auto pRootSignature = pSharedDevice->createRootSignature(2, 8);
	pRootSignature->initStaticSampler(0, ShaderHelper::getStaticSamplers());
	pRootSignature->at(0).initAsConstants(dx12lib::RegisterSlot::CBV0, sizeof(CBData) / sizeof(float));
	pRootSignature->at(1).initAsDescriptorTable({
		{ dx12lib::RegisterSlot::SRV0, 1 },
		{ dx12lib::RegisterSlot::UAV0, 1 },
	});
	pRootSignature->finalize();

	_pTemporalPipeline = pSharedDevice->createComputePSO("TemporalPipeline");
	_pTemporalPipeline->setComputeShader(g_TAAResolveCS, sizeof(g_TAAResolveCS));
	_pTemporalPipeline->setRootSignature(pRootSignature);
	_pTemporalPipeline->finalize();
}

void TemporalAAPass::execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) {
	ExecutablePass::execute(directCtx, view);

	constexpr size_t kNum32Bit = sizeof(CBData) / sizeof(float);
	CBData data;
	data.gResolution.x = static_cast<float>(view.viewport.width);
	data.gResolution.y = static_cast<float>(view.viewport.height);
	data.gResolution.z = 1.f / view.viewport.width;
	data.gResolution.w = 1.f / view.viewport.height;
	data.gJitter.x = view.xJitter;
	data.gJitter.y = view.yJitter;
	data.gFrameNumber = view.frameIndex;
	data.padding0 = 0;

	directCtx.setComputePSO(_pTemporalPipeline);
	directCtx.setCompute32BitConstants(dx12lib::RegisterSlot::CBV0, kNum32Bit, &data);
	directCtx.setUnorderedAccessView("gOutputMap", pOutputMap->get2dUAV());
	directCtx.setShaderResourceView("gScreenMap", pScreenMap->get2dSRV());
	auto dispatchArgs = _pTemporalPipeline->calcDispatchArgs(view.viewport.width, view.viewport.height);
	directCtx.dispatch(dispatchArgs);
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
	_pTemporalColor[1] = directCtx.createTexture(desc, &clearValue);
}

}
