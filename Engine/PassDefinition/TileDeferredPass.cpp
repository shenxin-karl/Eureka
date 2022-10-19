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
	: ExecutablePass(passName)
	, pDepthMap(this, "DepthMap")
	, pPointLightLists(this, "PointLightLists")
	, pTileLightLists(this, "TileLightLists")
	, _maxSpotLights(maxSpotLights)
	, _maxPointLights(maxPointLights)
{
	_pCbTile = directCtx.createFRConstantBuffer<CbTile>();

	auto pTileDeferredShader = ShaderManager::instance()->getComputeShader("TileDeferred");
	_pPipeline = pTileDeferredShader->getPSO();

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

void TileDeferredPass::preExecute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) {
	ExecutablePass::preExecute(pDirectCtx, view);
}

void TileDeferredPass::execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) {
	ExecutablePass::execute(pDirectCtx, view);

	const rgph::CameraData &cameraData = view.cameraData;
	//if (std::memcmp(&_matView, &cameraData.matView, sizeof(float4x4)) != 0) {
		_matView = cameraData.matView;
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
		//if (_maxSpotLights > 0) {
		//	pDirectCtx->setComputePSO(_pUpdateSpotLightBoundingSpherePipeline);
		//	const auto &srv = _pSpotLightBoundingSpheres->getSRV();
		//	pDirectCtx->setShaderResourceView(StringName("gSpotList"), srv);
		//	pDirectCtx->transitionBarrier(_pSpotLightBoundingSpheres, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
		//	const auto &uav = _pSpotLightBoundingSpheres->getUAV();
		//	pDirectCtx->setUnorderedAccessView(StringName("gOutputBoundingSphere"), uav);
		//	size_t numSpotLight = _pSpotLightBoundingSpheres->getElementCount();
		//	auto dispatchArgs = _pUpdatePointLightBoundingSpherePipeline->calcDispatchArgs(numSpotLight);
		//	pDirectCtx->dispatch(dispatchArgs);
		//	pDirectCtx->transitionBarrier(_pSpotLightBoundingSpheres, D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
		//}
	//}

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
