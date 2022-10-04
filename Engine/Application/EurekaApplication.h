#pragma once
#include "Application/Application.h"
#include "Model/MeshModel/MeshModel.h"


namespace Eureka {

class Camera;
class FPSCameraControl;

class EurekaApplication : public Application {
public:
	~EurekaApplication() override;
	void onInitialize(dx12lib::DirectContextProxy pDirectCtx) override;
	void onDestroy() override;
	void onBeginTick(std::shared_ptr<GameTimer> pGameTimer) override;
	void onTick(std::shared_ptr<GameTimer> pGameTimer) override;
	void onEndTick(std::shared_ptr<GameTimer> pGameTimer) override;
	void onResize(dx12lib::DirectContextProxy pDirectCtx, int width, int height) override;
private:
	void loading(dx12lib::DirectContextProxy pDirectCtx);
private:
	std::vector<std::unique_ptr<IModel>> _models;
	std::shared_ptr<Camera>				_pCamera;
	std::shared_ptr<FPSCameraControl>	_pCameraContorl;
public:
	std::shared_ptr<dx12lib::Texture>	_pGBuffer0;
	std::shared_ptr<dx12lib::Texture>	_pGBuffer1;
	std::shared_ptr<dx12lib::Texture>	_pGBuffer2;
	std::shared_ptr<rgph::RenderGraph>	_pRenderGraph;
};

}