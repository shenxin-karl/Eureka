#include "TileDeferredPass.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "EngineDefinition/EngineDefinition.h"
#include "ShaderHelper/ComputePipeline.h"
#include "ShaderHelper/PipelineManager.h"

using namespace Math;

namespace Eureka {

TileDeferredPass::TileDeferredPass(const std::string &passName, dx12lib::IDirectContext &directCtx, 
	size_t maxPointLights,
	size_t maxSpotLights)
: TileBased(passName, directCtx, maxPointLights, maxSpotLights)
, pDepthMap(this, "DepthMap")
{
	_pCbTile = directCtx.createFRConstantBuffer<CbTile>();
	auto pTileDeferredShader = PipelineManager::instance()->getComputePipeline("TileDeferred");
	_pPipeline = pTileDeferredShader->getPSO();
}

void TileDeferredPass::execute(dx12lib::IDirectContext &directCtx, const rgph::RenderView &view) {
	TileBased::execute(directCtx, view);

	if (!_needUpdateTile)
		return;

	const rgph::CameraData &cameraData = view.cameraData;
	auto visitor = _pCbTile->visit();
	visitor->gView = cameraData.matView;
	visitor->gProj = cameraData.matProj;
	visitor->gNear = cameraData.zNear;
	visitor->gFar = cameraData.zFar;
	visitor->gFarMultiplyNear = cameraData.zFar * cameraData.zNear;
	visitor->gFarMinusNear = cameraData.zFar - cameraData.zNear;

	const auto &desc = pDepthMap->getDesc();
	directCtx.setComputePSO(_pPipeline);
	directCtx.setConstantBufferView(StringName("gCbTile"), _pCbTile->getCBV());
	directCtx.setShaderResourceView(StringName("gDepthMap"), pDepthMap->get2dSRV());
	directCtx.setShaderResourceView(StringName("gPointLists"), pPointLightLists->getSRV());
	directCtx.setShaderResourceView(StringName("gPointBoundingSpheres"), _pPointLightBoundingSpheres->getSRV());
	directCtx.setUnorderedAccessView(StringName("gTileLightLists"), pTileLightLists->getUAV());
	auto dispatchArgs = _pPipeline->calcDispatchArgs(desc.Width, desc.Height);
	directCtx.dispatch(dispatchArgs);
}

}