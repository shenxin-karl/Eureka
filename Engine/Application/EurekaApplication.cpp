#include <Dx12lib/Device/DeviceStd.h>
#include <Dx12lib/Context/ContextStd.h>
#include <Dx12lib/Texture/Texture.h>
#include "EurekaApplication.h"

#include <random>

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
#include "Model/PartModel/PartModel.h"
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
	cameraDesc.farClip = 100.f;
	cameraDesc.fov = 45.f;
	cameraDesc.aspect = static_cast<float>(_width) / static_cast<float>(_height);
	_pCamera = std::make_shared<Camera>(cameraDesc);
	_pCameraControl = std::make_shared<FPSCameraControl>(_pCamera);

	pCbPrePass = pDirectCtx->createFRConstantBuffer<CbPrePass>();
	pCbLighting = pDirectCtx->createFRConstantBuffer<CbLighting>();
	auto visitor = pCbLighting->visit();
	visitor->gLightDirection = normalize(Vector3(0.1f, 0.7f, 0.3f)).xyz;
	visitor->gLightRadiance = float3(5.f);

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

	// update point light view space position
	//Math::Matrix4 matView = _pCamera->getMatView();
	//std::span<PointLight> visitor = pPointLightList->visit();
	//for (PointLight &pointLight : visitor)
	//	pointLight.viewSpacePosition = float4(matView * Vector4(pointLight.position, 1.0));
	
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

	float radian = DirectX::XMConvertToRadians(pGameTimer->getTotalTime() * 20.f);
	Quaternion q(Vector3(0, 1, 0), radian);

	auto visitor = pCbLighting->visit();
	visitor->gLightDirection = normalize(q * Vector3(0.1f, 0.7f, 0.3f)).xyz;

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
	resizeBuffers(pDirectCtx, width, height);
}

void EurekaApplication::loading(dx12lib::DirectContextProxy pDirectCtx) {
	MaterialDesc materialDesc {
		"DeferredPBR",
		nullptr,
		*pDirectCtx,
		pRenderGraph
	};
	auto materialCreator = [&](const ALMaterial *pAlMaterial) {
		materialDesc.pAlMaterial = pAlMaterial;
		return std::make_shared<Material>(materialDesc);
	};

	auto pSponzaPBR = std::make_shared<ALTree>("Assets/Models/SponzaPBR/Sponza.gltf");
	auto pModel = std::make_unique<MeshModel>(*pDirectCtx, pSponzaPBR);
	pModel->createMaterial(*pDirectCtx, materialCreator);
	pModel->setModelTransform(static_cast<float4x4>(Matrix4::makeScale(2.f)));
	_models.push_back(std::move(pModel));

	auto pCubeMesh = GeometryGenerator::instance()->createBox(0.5, 0.5, 0.5f, 1);
	auto pCubeModel = std::make_unique<PartModel>(*pDirectCtx, pCubeMesh);
	pCubeModel->createMaterial(*pDirectCtx, materialCreator);
	pCubeModel->setModelTransform(static_cast<float4x4>(Matrix4::makeTranslation(-3, 2, 1)));
	_models.push_back(std::move(pCubeModel));

	auto pCylinderMesh = GeometryGenerator::instance()->createCylinder(
		1.f, 
		0.f, 
		2.5, 20, 20
	);
	auto pCylinderModel = std::make_unique<PartModel>(*pDirectCtx, pCylinderMesh);
	pCylinderModel->createMaterial(*pDirectCtx, materialCreator);
	pCylinderModel->setModelTransform(static_cast<float4x4>(Matrix4::makeTranslation(0, 1, 1)));
	auto pCylinderMaterial = pCylinderModel->getMaterial();
	auto visitor = pCylinderMaterial->pCbMaterial->visit();
	visitor->diffuseAlbedo = float4(DirectX::Colors::DarkRed);
	_models.push_back(std::move(pCylinderModel));


	auto pSphereMesh = GeometryGenerator::instance()->createSphere(1.f, 5);
	auto pSphereModel = std::make_unique<PartModel>(*pDirectCtx, pSphereMesh);
	pSphereModel->createMaterial(*pDirectCtx, materialCreator);
	pSphereModel->setModelTransform(static_cast<float4x4>(Matrix4::makeTranslation(-5, 1, 0)));
	_models.push_back(std::move(pSphereModel));

	auto pSkullTree = std::make_shared<ALTree>("Assets/Models/Human skull.glb");
	auto pSkullModel = std::make_unique<MeshModel>(*pDirectCtx, pSkullTree);
	auto scale = Matrix4::makeScale(50.f);
	auto rotate = Matrix4::makeYRotationByDegree(-90.f);

	pSkullModel->setModelTransform(static_cast<float4x4>(scale * rotate));
	pSkullModel->createMaterial(*pDirectCtx, materialCreator);
	_models.push_back(std::move(pSkullModel));
}

void EurekaApplication::initPointLists(dx12lib::DirectContextProxy pDirectCtx) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis;

	constexpr float kRadius = 100.f;
	constexpr size_t kNumPointLights = 300;
	constexpr float kMinRange = 10.f;
	constexpr float kMaxRange = 20.f;

	std::vector<PointLight> pointLights;
	pointLights.reserve(kNumPointLights);
	for (size_t i = 0; i < kNumPointLights; ++i) {
		PointLight pointLight;
		pointLight.color = float3(dis(gen), dis(gen), dis(gen));
		pointLight.intensity = 3.f;
		pointLight.position = (Vector3(dis(gen), dis(gen), dis(gen)) * 2.f - 1.f * kRadius).xyz;
		pointLight.range = MathHelper::lerp(kMinRange, kMaxRange, dis(gen));
		pointLights.push_back(pointLight);
	}

	//pPointLightList = pDirectCtx->createFRStructuredBuffer<PointLight>(pointLights.data(), pointLights.size());
}

void EurekaApplication::initRenderGraph(dx12lib::DirectContextProxy pDirectCtx) {
	resizeBuffers(pDirectCtx, _width, _height);

	FXAASetting setting;
	pCbFXAASetting = pDirectCtx->createConstantBuffer(&setting, sizeof(setting));
	//pColorLutMap = pDirectCtx->createTextureFromFile(L"Assets/Textures/lut/color_grading_lut_02.png", false);
	pRenderGraph = SetupRenderGraph(this, *pDirectCtx);
}

void EurekaApplication::resizeBuffers(dx12lib::DirectContextProxy pDirectCtx, size_t width, size_t height) {
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

	pLightingBuffer = pDirectCtx->createTexture(dx12lib::Texture::make2D(
		kLightingBufferFormat,
		width,
		height,
		D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS
	));

	pPostProcessingBuffer = pDirectCtx->createTexture(dx12lib::Texture::make2D(
		kPostProcessingBufferFormat,
		width,
		height,
		D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS
	));

	//size_t numTile = MathHelper::divideByMultiple(width, TBDR_TILE_DIMENSION) * 
	//	MathHelper::divideByMultiple(height, TBDR_TILE_DIMENSION);
	//pTileLightLists = pDirectCtx->createFRStructuredBuffer<LightList>(numTile);
}

}
