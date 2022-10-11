#include "LightingPass.h"
#include "LightingPassCS.h"
#include "Dx12lib/Pipeline/PipelineStateObject.h"
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
	_pLightingPSO = pDevice->createComputePSO("LightingPSO");
	_pLightingPSO->setComputeShader(g_LightingPassCS, sizeof(g_LightingPassCS	));
	ShaderHelper::generateRootSignature(_pLightingPSO);
	_pLightingPSO->finalize();
}

void LightingPass::execute(dx12lib::DirectContextProxy pDirectCtx, const rgph::RenderView &view) {
	ExecutablePass::execute(pDirectCtx, view);

	const rgph::CameraData &cameraData = view.cameraData;
	float h = 2.f * std::tan(DirectX::XMConvertToRadians(cameraData.fov)) * cameraData.zNear;
	float w = h * cameraData.aspect;

	auto visitor = pCbLighting->visit();
	Vector3 down = h * -Vector3(cameraData.lookUp);
	Vector3 right = w * Vector3(cameraData.lookAt);
	Vector3 center = Vector3(cameraData.lookAt) * cameraData.zNear;
	Vector3 viewLeftTop = center - right / 2.f - down / 2.f;
	visitor->gProj = cameraData.matProj;
	visitor->gCameraPosition = float4(cameraData.lookFrom, 1.f);
	visitor->gViewLeftTop = float4(viewLeftTop.xyz, 1.f);
	visitor->gViewDownDir = float4(down.xyz, 1.f);
	visitor->gViewRightDir = float4(right.xyz, 1.f);

	const auto &desc = pDepthMap->getDesc();

	pDirectCtx->setComputePSO(_pLightingPSO);
	pDirectCtx->setConstantBufferView("CbLighting", pCbLighting->getCBV());
	pDirectCtx->setShaderResourceView("gBuffer0", pGBuffer0->get2dSRV());
	pDirectCtx->setShaderResourceView("gBuffer1", pGBuffer1->get2dSRV());
	pDirectCtx->setShaderResourceView("gBuffer2", pGBuffer2->get2dSRV());
	pDirectCtx->setShaderResourceView("gDepthMap", pDepthMap->get2dSRV());
	pDirectCtx->setUnorderedAccessView("gLightingBuffer", pLightingBuffer->get2dUAV());
	auto dispatchArgs = _pLightingPSO->calcDispatchArgs(desc.Width, desc.Height);
	pDirectCtx->dispatch(dispatchArgs);
}

}
