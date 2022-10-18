#include "TileDeferredPass.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "EngineDefinition/EngineDefinition.h"
#include "HlslShader/ShaderManager.h"
#include "ShaderHelper/ComputeShader.h"

namespace Eureka {

TileDeferredPass::TileDeferredPass(const std::string &passName, dx12lib::IDirectContext &directCtx)
	: ExecutablePass(passName)
	, pDepthMap(this, "DepthMap")
	, pPointLightLists(this, "PointLightLists")
	, pTileLightLists(this, "TileLightLists")
{
	_pCbTile = directCtx.createFRConstantBuffer<CbTile>();

	auto pTileDeferredShader = ShaderManager::instance()->getComputeShader("TileDeferred");
	_pPipeline = pTileDeferredShader->getPSO();
}

void TileDeferredPass::preExecute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) {
	ExecutablePass::preExecute(pDirectCtx, view);
}

void TileDeferredPass::execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) {
	ExecutablePass::execute(pDirectCtx, view);

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
	pDirectCtx->setUnorderedAccessView(StringName("gTileLightLists"), pTileLightLists->getUAV());
	auto dispatchArgs = _pPipeline->calcDispatchArgs(desc.Width, desc.Height);
	pDirectCtx->dispatch(dispatchArgs);
}
}
