#include <iostream>
#include <random>
#include <Dx12lib/Device/DeviceStd.h>
#include <Dx12lib/Context/ContextStd.h>
#include <Dx12lib/Texture/Texture.h>
#include <Dx12lib/Buffer/FRSRStructuredBuffer.hpp>
#include <Dx12lib/Buffer/ConstantBuffer.h>
#include <Dx12lib/Buffer/FRConstantBuffer.hpp>
#include <Dx12lib/Buffer/UAStructuredBuffer.h>
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
#include "EngineDefinition/EngineDefinition.h"
#include "Material/Material.h"
#include "Model/GeometryGenerator/GeometryGenerator.h"
#include "Model/PartModel/PartModel.h"
#include "PassDefinition/ClusterDeferredPass.h"
#include "RenderGraph/RenderGraph/RenderGraph.h"
#include "PassDefinition/SetupRenderGraph.h"
#include "TextureManager/TextureManager.h"

using namespace Math;

namespace Eureka {

EurekaApplication::EurekaApplication() {
	_width = 256;
	_height = 256;
}

EurekaApplication::~EurekaApplication() {
}

void EurekaApplication::onInitialize(dx12lib::DirectContextProxy pDirectCtx) {
	MeshManager::SingletionEmplace();
	TextureManager::SingletionEmplace();
	ShaderManager::SingletionEmplace();
	GeometryGenerator::SingletionEmplace();

	_pSwapChain->setVerticalSync(true);

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
	visitor->gDirectionalLight.direction = normalize(Vector3(0.1f, 0.7f, 0.3f)).xyz;
	visitor->gDirectionalLight.directionalColor = float3(1.f);
	visitor->gDirectionalLight.directionalIntensity = 5.f;
	visitor->gDirectionalLight.ambientColor = float3(0.1f);
	visitor->gDirectionalLight.ambientIntensity = 1.f;

	initLight(pDirectCtx);
	initRenderGraph(pDirectCtx);

	//MaterialDesc materialDesc{
	//	"DeferredPBR",
	//	nullptr,
	//	*pDirectCtx,
	//	pRenderGraph
	//};
	//auto materialCreator = [&](const ALMaterial *pAlMaterial) {
	//	materialDesc.pAlMaterial = pAlMaterial;
	//	return std::make_shared<Material>(materialDesc);
	//};

	//auto pSphereMesh = GeometryGenerator::instance()->createSphere(0.15f, 5);
	//auto pointLightVisitor = pPointLightList->visit();
	//for (PointLight &pointLight : pointLightVisitor) {
	//	auto pSphereModel = std::make_unique<PartModel>(*pDirectCtx, pSphereMesh);
	//	pSphereModel->setModelTransform(float4x4(Matrix4::makeTranslation(Vector3(pointLight.position))));
	//	pSphereModel->createMaterial(*pDirectCtx, materialCreator);
	//	_models.push_back(std::move(pSphereModel));
	//}

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

	float fWidth = static_cast<float>(_width);
	float fHeight = static_cast<float>(_height);
	Matrix4 matClipToViewport = Matrix4::makeScale(fWidth, fHeight, 1.f)
							  * Matrix4::makeTranslation(0.5f, 0.5f, 0.f)
							  * Matrix4::makeScale(0.5f, -0.5f, 1.f);

	uint64_t frameIndex = dx12lib::FrameIndexProxy::getFrameResourceIndex();
	float2 jitterOffset = kHalton23[frameIndex % 8];
	xJitter = jitterOffset.x / fWidth;
	yJitter = jitterOffset.y / fHeight;

	DX::XMMATRIX matProj = DX::XMLoadFloat4x4(RVPtr(_pCamera->getProj()));
	matProj.r[2].m128_f32[0] += xJitter;//_31
	matProj.r[2].m128_f32[1] += yJitter;//_32

	Matrix4 preFrameViewProj(prevFrameMatViewProj);
	Matrix4 matView = _pCamera->getMatView();

	//pCbPrePassVisitor->gMatJitterViewProj = float4x4(Matrix4(matProj) * matView);
	pCbPrePassVisitor->gMatJitterViewProj = pCbPrePassVisitor->matViewProj;
	pCbPrePassVisitor->gMatViewport = float4x4(matClipToViewport * _pCamera->getMatViewProj());
	pCbPrePassVisitor->gMatPreViewport = float4x4(matClipToViewport * preFrameViewProj);

	prevFrameMatViewProj = _pCamera->getViewProj();
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
	view.viewport.width = _width;
	view.viewport.height = _height;
	view.frameIndex = dx12lib::FrameIndexProxy::getFrameIndex();
	view.xJitter = xJitter;
	view.yJitter = yJitter;

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
	pRenderGraph->onResize(pDirectCtx, width, height);
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

void EurekaApplication::initLight(dx12lib::DirectContextProxy pDirectCtx) {
	auto seed = 601319370;;
	std::mt19937 gen(seed);
	std::uniform_real_distribution<float> dis;

	constexpr float kRadius = 18.f;
	constexpr size_t kNumPointLights = 1000;
	constexpr float kMinRange = 1.f;
	constexpr float kMaxRange = 5.f;
	constexpr float kMinInnerConeAngle = 30.f;
	constexpr float kMaxInnerConeAngle = 50.f;

	std::vector<PointLight> pointLights;
	pointLights.reserve(kNumPointLights);
	for (size_t i = 0; i < kNumPointLights; ++i) {
		PointLight pointLight;
		pointLight.color = float3(dis(gen), dis(gen), dis(gen));
		pointLight.intensity = 5.f;
		pointLight.position = ((Vector3(dis(gen), dis(gen), dis(gen)) * 2.f - 1.f) * kRadius).xyz;
		pointLight.position.y = MathHelper::lerp(0.f, 13.f, dis(gen));
		pointLight.range = MathHelper::lerp(kMinRange, kMaxRange, dis(gen));
		pointLights.push_back(pointLight);
	}

	//pointLights.back().range = 5000.f;
	pPointLightList = pDirectCtx->createFRStructuredBuffer<PointLight>(pointLights.data(), pointLights.size());

	std::vector<SpotLight> spotLights;
	spotLights.reserve(kNumPointLights);
	for (size_t i = 0; i < kNumPointLights; ++i) {
		SpotLight spotLight;
		spotLight.color = float3(dis(gen), dis(gen), dis(gen));
		spotLight.intensity = 5.f;
		spotLight.position = ((Vector3(dis(gen), dis(gen), dis(gen)) * 2.f - 1.f) * kRadius).xyz;
		spotLight.position.y = MathHelper::lerp(0.f, 13.f, dis(gen));
		spotLight.range = MathHelper::lerp(kMinRange, kMaxRange, dis(gen));
		spotLight.direction = normalize(Vector3(dis(gen), dis(gen), dis(gen)) * 2.f - 1.f).xyz;

		float innerConeAngle = MathHelper::lerp(kMinInnerConeAngle, kMaxInnerConeAngle, dis(gen));
		float outerConeAngle = innerConeAngle + 15.f;
		spotLight.outerConeCosTheta = std::cos(DirectX::XMConvertToRadians(outerConeAngle));
		spotLight.innerConeCosTheta = std::cos(DirectX::XMConvertToRadians(innerConeAngle));

		float e0 = spotLight.range / 2.f;
		float e1 = std::sin(DirectX::XMConvertToRadians(outerConeAngle)) * spotLight.range;
		float radius = std::sqrt(e0 * e0 + e1 * e1);
		spotLight.boundingSphereRadius = radius;

		spotLights.push_back(spotLight);

	}

	pSpotLightList = pDirectCtx->createFRStructuredBuffer<SpotLight>(spotLights.data(), spotLights.size());
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

	pTemporalOutput = pDirectCtx->createTexture(dx12lib::Texture::make2D(
		kTemporalAAFormat,
		width,
		height,
		D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS
	));
	pTemporalOutput->setResourceName("TemporalOutputMap");

	pVelocityMap = pDirectCtx->createTexture(dx12lib::Texture::make2D(
		kVelocityFormat,
		width,
		height,
		D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	));
	pVelocityMap->setResourceName("VelocityMap");

	size_t numTile = MathHelper::divideByMultiple(width, TBDR_TILE_DIMENSION) * 
		MathHelper::divideByMultiple(height, TBDR_TILE_DIMENSION);
	pTileLightLists = pDirectCtx->createUAStructuredBuffer(nullptr, numTile, sizeof(LightList));
	pTileLightLists->setResourceName("TileLightLists");

	size_t numClusterTile = ClusterDeferredPass::calcTileSize(_width, _height, _pCamera->getFarClip());
	pTileClusterLightList = pDirectCtx->createUAStructuredBuffer(nullptr, numClusterTile, sizeof(LightList));
}

}
