#include "LightingPass.h"
#include "LightingPassCS.h"
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

	const rgph::CameraData &cameraData = view.cameraData;
	float h = 2.f * std::tan(DirectX::XMConvertToRadians(cameraData.fov)) * cameraData.zNear;
	float w = h * cameraData.aspect;

	auto visitor = pCbLighting->visit();
	Vector3 lookUp(cameraData.lookUpDir);
	Vector3 lookAt(cameraData.lookAtDir);
	Vector3 lookRight = normalize(cross(lookAt, lookUp));

	const auto &desc = pDepthMap->getDesc();

	Vector3 down = h * -lookUp; 
	Vector3 right = w * lookRight;
	Vector3 center = lookAt * cameraData.zNear;
	Vector3 viewLeftTop = center - right / 2.f - down / 2.f;
	visitor->gProj = cameraData.matProj;
	visitor->gCameraPosition = cameraData.lookFrom;
	visitor->gViewLeftTop = viewLeftTop.xyz;
	visitor->gViewDownDir = down.xyz;
	visitor->gViewRightDir = right.xyz;
	visitor->gWidth = static_cast<float>(desc.Width);
	visitor->gHeight = static_cast<float>(desc.Height);
	visitor->padding0 = 0.f;
	visitor->padding1 = 0.f;

	pDirectCtx->setComputePSO(_pLightingPSO);
	pDirectCtx->setConstantBufferView("CbLighting", pCbLighting->getCBV());
	//pDirectCtx->setShaderResourceView("gBuffer0", pGBuffer0->get2dSRV());
	//pDirectCtx->setShaderResourceView("gBuffer1", pGBuffer1->get2dSRV());
	//pDirectCtx->setShaderResourceView("gBuffer2", pGBuffer2->get2dSRV());
	pDirectCtx->setShaderResourceView("gDepthMap", pDepthMap->get2dSRV());
	pDirectCtx->setUnorderedAccessView("gLightingBuffer", pLightingBuffer->get2dUAV());
	auto dispatchArgs = _pLightingPSO->calcDispatchArgs(desc.Width, desc.Height);
	pDirectCtx->dispatch(dispatchArgs);
}

}
