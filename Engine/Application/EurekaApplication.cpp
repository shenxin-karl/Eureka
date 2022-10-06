#include <Dx12lib/Device/DeviceStd.h>
#include <Dx12lib/Context/ContextStd.h>
#include <Dx12lib/Texture/Texture.h>
#include "EurekaApplication.h"
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
	ShaderManager::instance()->loading(_pDevice);
	loading(pDirectCtx);
}

void EurekaApplication::onDestroy() {
	ShaderManager::SingletionDestory();
	TextureManager::SingletionDestory();
	MeshManager::SingletionDestory();
}

void EurekaApplication::onBeginTick(std::shared_ptr<GameTimer> pGameTimer) {
	_pCameraControl->update(_pInputSystem, pGameTimer);
}

void EurekaApplication::onTick(std::shared_ptr<GameTimer> pGameTimer) {
	auto pCmdQueue = _pDevice->getCommandQueue();
	auto pDirectProxy = pCmdQueue->createDirectContextProxy();
	float cosine = std::cos(pGameTimer->getTotalTime());
	float sine = std::sin(pGameTimer->getTotalTime());
	float4 color = {
		cosine * 0.5f + 0.5f,
		sine * 0.5f + 0.5f,
		0.6f,
		1.f
	};

	D3D12_VIEWPORT viewport = {
		.TopLeftX = 0.f,
		.TopLeftY = 0.f,
		.Width = static_cast<float>(_width),
		.Height = static_cast<float>(_height),
		.MinDepth = 0.f,
		.MaxDepth = 1.f
	};

	D3D12_RECT scissorRect{
		.left = 0,
		.top = 0,
		.right = static_cast<LONG>(_width),
		.bottom = static_cast<LONG>(_height),
	};
	auto pRenderTarget2D = _pSwapChain->getRenderTarget2D();
	auto pDepthStencil2D = _pSwapChain->getDepthStencil2D();

	pDirectProxy->setViewport(viewport);
	pDirectProxy->setScissorRect(scissorRect);
	pDirectProxy->transitionBarrier(_pSwapChain->getRenderTarget2D(), D3D12_RESOURCE_STATE_RENDER_TARGET);
	{
		pDirectProxy->setRenderTarget(pRenderTarget2D->get2dRTV(), pDepthStencil2D->get2dDSV());
		pDirectProxy->clearColor(pRenderTarget2D->get2dRTV(), color);
	}
	pDirectProxy->transitionBarrier(pRenderTarget2D, D3D12_RESOURCE_STATE_PRESENT);
	pCmdQueue->executeCommandList(pDirectProxy);
}

void EurekaApplication::onEndTick(std::shared_ptr<GameTimer> pGameTimer) {
	auto pCmdQueue = _pDevice->getCommandQueue();
	pCmdQueue->signal(_pSwapChain);
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
	pRenderGraph = SetupRenderGraph(this);
}

void EurekaApplication::resizeGBuffer(dx12lib::DirectContextProxy pDirectCtx, size_t width, size_t height) {
	pGBuffer0 = pDirectCtx->createTexture(dx12lib::Texture::make2D(
		kGBuffer0Format, width, height, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	));
	pGBuffer1 = pDirectCtx->createTexture(dx12lib::Texture::make2D(
		kGBuffer1Format, width, height, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	));
	pGBuffer2 = pDirectCtx->createTexture(dx12lib::Texture::make2D(
		kGBuffer2Format, width, height, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	));
}

}
