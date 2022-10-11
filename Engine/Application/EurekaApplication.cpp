#include <Dx12lib/Device/DeviceStd.h>
#include <Dx12lib/Context/ContextStd.h>
#include <Dx12lib/Texture/Texture.h>
#include "EurekaApplication.h"

#include <iostream>

#include "InputSystem/InputSystem.h"
#include "InputSystem/window.h"
#include "GameTimer/GameTimer.h"
#include "Model/MeshManager.h"
#include "ShaderHelper/GraphicsShader.h"
#include "HlslShader/ShaderManager.h"
#include "AssimpLoader/ALTree.h"
#include "Camera/Camera.h"
#include "Camera/FPSCameraControl.h"
#include "Defined/EngineDefined.h"
#include "Material/Material.h"
#include "Model/GeometryGenerator/GeometryGenerator.h"
#include "RenderGraph/RenderGraph/RenderGraph.h"
#include "RenderGraphDefined/RenderGraphDefined.h"
#include "TextureManager/TextureManager.h"

using namespace Math;

namespace Eureka {

EurekaApplication::~EurekaApplication() {
}

void EurekaApplication::onInitialize(dx12lib::DirectContextProxy pDirectCtx) {
	MeshManager::SingletionEmplace();
	TextureManager::SingletionEmplace();
	ShaderManager::SingletionEmplace();
	GeometryGenerator::SingletionEmplace();

	_pSwapChain->setVerticalSync(false);

	ShaderManager::instance()->loading(_pDevice);
	GeometryGenerator::instance()->loading();

	CameraDesc cameraDesc;
	cameraDesc.lookAt = float3(0, 0, 0);
	cameraDesc.lookFrom = float3(5, 0, 0);
	cameraDesc.lookUp = float3(0, 1, 0);
	cameraDesc.nearClip = 0.1f;
	cameraDesc.farClip = 1000.f;
	cameraDesc.fov = 45.f;
	cameraDesc.aspect = static_cast<float>(_width) / static_cast<float>(_height);
	_pCamera = std::make_shared<Camera>(cameraDesc);
	_pCameraControl = std::make_shared<FPSCameraControl>(_pCamera);

	pCbPrePass = pDirectCtx->createFRConstantBuffer<CbPrePass>();
	initRenderGraph(pDirectCtx);

	// loading
	loading(pDirectCtx);
}

void EurekaApplication::onDestroy() {
	GeometryGenerator::SingletionDestory();
	ShaderManager::SingletionDestory();
	TextureManager::SingletionDestory();
	MeshManager::SingletionDestory();
}

void EurekaApplication::onBeginTick(std::shared_ptr<GameTimer> pGameTimer) {
	_pCameraControl->update(_pInputSystem, pGameTimer);

	auto pCbPrePassVisitor = pCbPrePass->visit();
	pCbPrePassVisitor->matView = _pCamera->getView();
	pCbPrePassVisitor->matInvView = _pCamera->getInvView();
	pCbPrePassVisitor->matProj = _pCamera->getProj();
	pCbPrePassVisitor->matInvProj = _pCamera->getInvProj();
	pCbPrePassVisitor->matViewProj = _pCamera->getViewProj();
	pCbPrePassVisitor->matInvViewProj = _pCamera->getInvViewProj();
	pCbPrePassVisitor->cameraPos = _pCamera->getLookFrom();
	pCbPrePassVisitor->nearClip = _pCamera->getNearClip();
	pCbPrePassVisitor->cameraLookUp = _pCamera->getLookUp();
	pCbPrePassVisitor->farClip = _pCamera->getFarClip();
	pCbPrePassVisitor->cameraLookAt = _pCamera->getLookAt();
	pCbPrePassVisitor->cbPrePassPadding0 = 0.f;
	pCbPrePassVisitor->renderTargetSize = _pSwapChain->getRenderTargetSize();
	pCbPrePassVisitor->invRenderTargetSize = _pSwapChain->getInvRenderTargetSize();
	pCbPrePassVisitor->totalTime = pGameTimer->getTotalTime();
	pCbPrePassVisitor->deltaTime = pGameTimer->getDeltaTime();
	pCbPrePassVisitor->fogColor = float4(0.f);
	pCbPrePassVisitor->fogStart = 0.f;
	pCbPrePassVisitor->fogEnd = 0.f;
	pCbPrePassVisitor->cbPrePassPadding1 = float2(0.f);

	if (pGameTimer->oneSecondTrigger()) {
		std::string titleName = std::format("{} fps:{} mspf:{} ", _title, pGameTimer->FPS(), pGameTimer->mspf());
		_pInputSystem->pWindow->setShowTitle(titleName);
	}
}

void EurekaApplication::onTick(std::shared_ptr<GameTimer> pGameTimer) {
	auto pCmdQueue = _pDevice->getCommandQueue();
	auto pDirectProxy = pCmdQueue->createDirectContextProxy();

	auto boundWrap = MakeBoundingWrap(_pCamera->getViewSpaceFrustum());
	for (auto &pModel : _models)
		pModel->submit(boundWrap, kTechGBuffer);

	dx12lib::RenderProfiler profiler;
	rgph::RenderView view;
	view.cameraData = _pCamera->getCameraData();
	view.pProfiler = &profiler;

	pRenderGraph->execute(pDirectProxy, view);
	pCmdQueue->executeCommandList(pDirectProxy);
}

void EurekaApplication::onEndTick(std::shared_ptr<GameTimer> pGameTimer) {
	auto pCmdQueue = _pDevice->getCommandQueue();
	pCmdQueue->signal(_pSwapChain);
	pRenderGraph->reset();
}

void EurekaApplication::onResize(dx12lib::DirectContextProxy pDirectCtx, int width, int height) {
	_pCamera->setAspect(static_cast<float>(width) / static_cast<float>(height));
	resizeGBuffer(pDirectCtx, width, height);
}

void EurekaApplication::loading(dx12lib::DirectContextProxy pDirectCtx) {
	auto pSponzaPBR = std::make_shared<ALTree>("Assets/Models/SponzaPBR/Sponza.gltf");
	auto pModel = std::make_unique<MeshModel>(*pDirectCtx, pSponzaPBR);

	MaterialDesc materialDesc {
		"DeferredPBR",
		nullptr,
		*pDirectCtx,
		pRenderGraph
	};
	pModel->createMaterial(*pRenderGraph, *pDirectCtx, [&](const ALMaterial *pAlMaterial) {
		materialDesc.pAlMaterial = pAlMaterial;
		return std::make_shared<Material>(materialDesc);
	});

	_models.push_back(std::move(pModel));
}

void EurekaApplication::initRenderGraph(dx12lib::DirectContextProxy pDirectCtx) {
	resizeGBuffer(pDirectCtx, _width, _height);

	FXAASetting setting;
	pCbFXAASetting = pDirectCtx->createConstantBuffer(&setting, sizeof(setting));

	pRenderGraph = SetupRenderGraph(this, *pDirectCtx);
}

void EurekaApplication::resizeGBuffer(dx12lib::DirectContextProxy pDirectCtx, size_t width, size_t height) {
	pGBuffer0 = pDirectCtx->createTexture(dx12lib::Texture::make2D(
		kGBuffer0Format, 
		width, 
		height, 
		D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	));
	pGBuffer0->setResourceName("GBuffer0");

	pGBuffer1 = pDirectCtx->createTexture(dx12lib::Texture::make2D(
		kGBuffer1Format, 
		width,
		height, 
		D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	));
	pGBuffer1->setResourceName("GBuffer1");


	pGBuffer2 = pDirectCtx->createTexture(dx12lib::Texture::make2D(
		kGBuffer2Format,
		width, 
		height, 
		D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	));
	pGBuffer2->setResourceName("GBuffer2");
}

}
