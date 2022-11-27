#pragma once
#include "Application/Application.h"
#include "Model/MeshModel/MeshModel.h"
#include "ShaderHelper/CBufferStruct.h"

namespace Eureka {

class Camera;
class FPSCameraControl;

class EurekaApplication : public Application {
public:
	EurekaApplication();
	~EurekaApplication() override;
	void onInitialize(dx12lib::DirectContextProxy pDirectCtx) final;
	void onDestroy() final;
	void onBeginTick(std::shared_ptr<GameTimer> pGameTimer) final;
	void onTick(std::shared_ptr<GameTimer> pGameTimer) final;
	void onEndTick(std::shared_ptr<GameTimer> pGameTimer) final;
	void onResize(dx12lib::DirectContextProxy pDirectCtx, int width, int height) final;
private:
	void loading(dx12lib::DirectContextProxy pDirectCtx);
	void initLight(dx12lib::DirectContextProxy pDirectCtx);
	void initRenderGraph(dx12lib::DirectContextProxy pDirectCtx);
	void resizeBuffers(dx12lib::DirectContextProxy pDirectCtx, size_t width, size_t height);
private:
	std::vector<std::unique_ptr<IModel>> _models;
	std::shared_ptr<Camera>				_pCamera;
	std::shared_ptr<FPSCameraControl>	_pCameraControl;
public:
	std::shared_ptr<dx12lib::Texture>	pGBuffer0;
	std::shared_ptr<dx12lib::Texture>	pGBuffer1;
	std::shared_ptr<dx12lib::Texture>	pGBuffer2;
	std::shared_ptr<dx12lib::Texture>	pLightingBuffer;
	std::shared_ptr<dx12lib::Texture>	pPostProcessingBuffer;
	std::shared_ptr<dx12lib::Texture>	pColorLutMap;
	std::shared_ptr<dx12lib::Texture>	pTemporalOutput;
	std::shared_ptr<dx12lib::Texture>	pVelocityMap;	// x: 0~width, y: 0~height, z: 0~1
	std::shared_ptr<rgph::RenderGraph>	pRenderGraph;

	float xJitter = 0.f;
	float yJitter = 0.f;

	dx12lib::FRConstantBufferPtr<CbPrePass>			pCbPrePass;
	dx12lib::FRConstantBufferPtr<CbLighting>		pCbLighting;
	dx12lib::FRStructuredBufferPtr<PointLight>		pPointLightList;
	dx12lib::FRStructuredBufferPtr<SpotLight>		pSpotLightList;
	std::shared_ptr<dx12lib::UAStructuredBuffer>	pTileLightLists;
	std::shared_ptr<dx12lib::UAStructuredBuffer>	pTileClusterLightList;
	std::shared_ptr<dx12lib::ConstantBuffer>		pCbFXAASetting;
};

}