#include "TileBased.h"

#include "Dx12lib/Context/ContextProxy.hpp"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "Dx12lib/Pipeline/RootSignature.h"
#include "EngineDefinition/EngineDefinition.h"
#include "EngineShaders/UpdatePointLightBoundingSphere_CS.h"
#include "EngineShaders/UpdateSpotLightBoundingSphere_CS.h"
#include "RenderGraph/Utility/Utility.h"

using namespace Math;

namespace Eureka {

TileBased::TileBased(const std::string &passName, 
	dx12lib::IDirectContext &directCtx, 
	size_t maxPointLights, 
	size_t maxSpotLights)
: ExecutablePass(passName)
, _maxSpotLights(maxSpotLights)
, _maxPointLights(maxPointLights)
, pPointLightLists(this, "PointLightLists")
, pTileLightLists(this, "TileLightLists")
{
	if (maxPointLights > 0)
		_pPointLightBoundingSpheres = directCtx.createUAStructuredBuffer(nullptr, maxPointLights, sizeof(float4));
	if (maxSpotLights > 0)
		_pSpotLightBoundingSpheres = directCtx.createUAStructuredBuffer(nullptr, maxSpotLights, sizeof(float4));

	auto pSharedDevice = directCtx.getDevice().lock();
	auto pRootSignature = pSharedDevice->createRootSignature(2);
	pRootSignature->at(0).initAsConstants(dx12lib::RegisterSlot::CBV0, 16);
	pRootSignature->at(1).initAsDescriptorTable({
		{ dx12lib::RegisterSlot::SRV0, 1 },
		{ dx12lib::RegisterSlot::UAV0, 1 },
	});
	pRootSignature->finalize();

	_pUpdatePointLightBoundingSpherePipeline = pSharedDevice->createComputePSO("UpdateSpotLightBoundingSpherePSO");
	_pUpdatePointLightBoundingSpherePipeline->setComputeShader(
		g_UpdatePointLightBoundingSphere_CS,
		sizeof(g_UpdatePointLightBoundingSphere_CS)
	);
	_pUpdatePointLightBoundingSpherePipeline->setRootSignature(pRootSignature);
	_pUpdatePointLightBoundingSpherePipeline->finalize();

	_pUpdateSpotLightBoundingSpherePipeline = pSharedDevice->createComputePSO("UpdateSpotLightBoundingSpherePipePSO");
	_pUpdateSpotLightBoundingSpherePipeline->setComputeShader(
		g_UpdateSpotLightBoundingSphere_CS,
		sizeof(g_UpdateSpotLightBoundingSphere_CS)
	);
	_pUpdateSpotLightBoundingSpherePipeline->setRootSignature(pRootSignature);
	_pUpdateSpotLightBoundingSpherePipeline->finalize();
}

void TileBased::execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) {
	ExecutablePass::execute(pDirectCtx, view);
	_needUpdate = _needUpdate || std::memcmp(&_matView, &view.cameraData.matView, sizeof(float4x4)) != 0;
	if (_needUpdate) {
		if (_maxPointLights > 0) {
			pDirectCtx->setComputePSO(_pUpdatePointLightBoundingSpherePipeline);
			pDirectCtx->setCompute32BitConstants(dx12lib::RegisterSlot::CBV0, 16, &_matView);
			const auto &srv = pPointLightLists->getSRV();
			pDirectCtx->setShaderResourceView(StringName("gPointList"), srv);
			pDirectCtx->transitionBarrier(_pPointLightBoundingSpheres, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
			const auto &uav = _pPointLightBoundingSpheres->getUAV();
			pDirectCtx->setUnorderedAccessView(StringName("gOutputBoundingSphere"), uav);
			size_t numPointLight = pPointLightLists->getElementCount();
			auto dispatchArgs = _pUpdatePointLightBoundingSpherePipeline->calcDispatchArgs(numPointLight);
			pDirectCtx->dispatch(dispatchArgs);
			pDirectCtx->transitionBarrier(_pPointLightBoundingSpheres, D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
		}
	}
}

void TileBased::postExecute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) {
	ExecutablePass::postExecute(pDirectCtx, view);
	_matView = view.cameraData.matView;
	_needUpdate = false;
}

void TileBased::onResize(dx12lib::DirectContextProxy pDirectCtx, size_t width, size_t height) {
	ExecutablePass::onResize(pDirectCtx, width, height);
	_needUpdate = true;
}


}
