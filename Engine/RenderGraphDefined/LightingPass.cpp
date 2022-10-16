#include "LightingPass.h"
#include "EngineShaders/LightingPassCS.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
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
	//_pLightingPSO = pDevice->createComputePSO("LightingPSO");
	//_pLightingPSO->setComputeShader(g_LightingPassCS, sizeof(g_LightingPassCS	));
	//ShaderHelper::generateRootSignature(_pLightingPSO);
	//_pLightingPSO->finalize();

	auto pLightShader = ShaderManager::instance()->getComputeShader("Lighting");
	_pLightingPSO = pLightShader->getPSO();
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
	pDirectCtx->setConstantBufferView("CbLighting", pCbLighting->getCBV());
	pDirectCtx->setShaderResourceView("gBuffer0", pGBuffer0->get2dSRV());
	pDirectCtx->setShaderResourceView("gBuffer1", pGBuffer1->get2dSRV());
	pDirectCtx->setShaderResourceView("gBuffer2", pGBuffer2->get2dSRV());
	pDirectCtx->setShaderResourceView("gDepthMap", pDepthMap->get2dSRV());
	pDirectCtx->setUnorderedAccessView("gLightingBuffer", pLightingBuffer->get2dUAV());
	pDirectCtx->setShaderResourceView("gPointLights", pPointLightLists->getSRV());
	pDirectCtx->setShaderResourceView("gTileLightLists", pTileLightLists->getSRV());
	auto dispatchArgs = _pLightingPSO->calcDispatchArgs(desc.Width, desc.Height);
	pDirectCtx->dispatch(dispatchArgs);
}

}
