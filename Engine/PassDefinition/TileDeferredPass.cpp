#include "TileDeferredPass.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "Dx12lib/Pipeline/RootSignature.h"
#include "EngineDefinition/EngineDefinition.h"
#include "HlslShader/ShaderManager.h"
#include "ShaderHelper/ComputeShader.h"

#include "EngineShaders/UpdatePointLightBoundingSphere_CS.h"
#include "EngineShaders/UpdateSpotLightBoundingSphere_CS.h"

using namespace Math;

namespace Eureka {

TileDeferredPass::TileDeferredPass(const std::string &passName, dx12lib::IDirectContext &directCtx, 
	size_t maxPointLights,
	size_t maxSpotLights)
: TileBased(passName, directCtx, maxPointLights, maxSpotLights)
, pDepthMap(this, "DepthMap")
{
	_pCbTile = directCtx.createFRConstantBuffer<CbTile>();
	auto pTileDeferredShader = ShaderManager::instance()->getComputeShader("TileDeferred");
	_pPipeline = pTileDeferredShader->getPSO();
}

void TileDeferredPass::execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) {
	TileBased::execute(pDirectCtx, view);

	const rgph::CameraData &cameraData = view.cameraData;
	auto visitor = _pCbTile->visit();
	visitor->gView = cameraData.matView;
	visitor->gProj = cameraData.matProj;
	visitor->gNear = cameraData.zNear;
	visitor->gFar = cameraData.zFar;
	visitor->gFarMultiplyNear = cameraData.zFar * cameraData.zNear;
	visitor->gFarMinusNear = cameraData.zFar - cameraData.zNear;

	const auto &desc = pDepthMap->getDesc();
	pDirectCtx->setComputePSO(_pPipeline);
	pDirectCtx->setConstantBufferView(StringName("gCbTile"), _pCbTile->getCBV());
	pDirectCtx->setShaderResourceView(StringName("gDepthMap"), pDepthMap->get2dSRV());
	pDirectCtx->setShaderResourceView(StringName("gPointLists"), pPointLightLists->getSRV());
	pDirectCtx->setShaderResourceView(StringName("gPointBoundingSpheres"), _pPointLightBoundingSpheres->getSRV());
	pDirectCtx->setUnorderedAccessView(StringName("gTileLightLists"), pTileLightLists->getUAV());
	auto dispatchArgs = _pPipeline->calcDispatchArgs(desc.Width, desc.Height);
	pDirectCtx->dispatch(dispatchArgs);
}

}