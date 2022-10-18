#include "LightingPass.h"
#include "EngineShaders/LightingPassCS.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
#include "EngineDefinition/EngineDefinition.h"
#include "HlslShader/ShaderManager.h"
#include "ShaderHelper/ComputeShader.h"
#include "ShaderHelper/ShaderHelper.h"

using namespace Math;

namespace Eureka {

LightingPass::LightingPass(const std::string &passName, std::shared_ptr<dx12lib::Device> pDevice)
	: ExecutablePass(passName)
	, pGBuffer0(this, "GBuffer0")
	, pGBuffer1(this, "GBuffer1")
	, pGBuffer2(this, "GBuffer2")
	, pDepthMap(this, "DepthMap")
	, pLightingBuffer(this, "LightingBuffer")
	, pPointLightLists(this, "PointLightLists")
	, pTileLightLists(this, "TileLightLists")
{
#if defined(_DEBUG) || defined(DEBUG)
	auto pLightShader = ShaderManager::instance()->getComputeShader("Lighting");
	_pLightingPSO = pLightShader->getPSO();
#else
	_pLightingPSO = pDevice->createComputePSO("LightingPSO");
	_pLightingPSO->setComputeShader(g_LightingPassCS, sizeof(g_LightingPassCS	));
	ShaderHelper::generateRootSignature(_pLightingPSO);
	_pLightingPSO->finalize();
#endif
}

void LightingPass::execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) {
	ExecutablePass::execute(pDirectCtx, view);

	const auto &desc = pDepthMap->getDesc();
	const rgph::CameraData &cameraData = view.cameraData;
	auto visitor = pCbLighting->visit();
	visitor->gClosedIntervalOfWidth = static_cast<float>(desc.Width) - 1.f;
	visitor->gClosedIntervalOfHeight = static_cast<float>(desc.Height) - 1.f;
	visitor->gInvViewProj = cameraData.matInvViewProj;
	visitor->gCameraPosition = cameraData.lookFrom;

	pDirectCtx->setComputePSO(_pLightingPSO);
	pDirectCtx->setConstantBufferView(StringName("CbLighting"), pCbLighting->getCBV());
	pDirectCtx->setShaderResourceView(StringName("gBuffer0"), pGBuffer0->get2dSRV());
	pDirectCtx->setShaderResourceView(StringName("gBuffer1"), pGBuffer1->get2dSRV());
	pDirectCtx->setShaderResourceView(StringName("gBuffer2"), pGBuffer2->get2dSRV());
	pDirectCtx->setShaderResourceView(StringName("gDepthMap"), pDepthMap->get2dSRV());
	pDirectCtx->setUnorderedAccessView(StringName("gLightingBuffer"), pLightingBuffer->get2dUAV());
	pDirectCtx->setShaderResourceView(StringName("gPointLights"), pPointLightLists->getSRV());
	pDirectCtx->setShaderResourceView(StringName("gTileLightLists"), pTileLightLists->getSRV());
	auto dispatchArgs = _pLightingPSO->calcDispatchArgs(desc.Width, desc.Height);
	pDirectCtx->dispatch(dispatchArgs);
}

}
