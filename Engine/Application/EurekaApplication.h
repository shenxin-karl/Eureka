#pragma once
#include "Application/Application.h"
#include "Model/MeshModel/MeshModel.h"
#include "ShaderHelper/CBufferStruct.h"

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
	void initRenderGraph(dx12lib::DirectContextProxy pDirectCtx);
	void resizeGBuffer(dx12lib::DirectContextProxy pDirectCtx, size_t width, size_t height);
private:
	std::vector<std::unique_ptr<IModel>> _models;
	std::shared_ptr<Camera>				_pCamera;
	std::shared_ptr<FPSCameraControl>	_pCameraControl;
public:
	std::shared_ptr<dx12lib::Texture>	pGBuffer0;
	std::shared_ptr<dx12lib::Texture>	pGBuffer1;
	std::shared_ptr<dx12lib::Texture>	pGBuffer2;
	std::shared_ptr<rgph::RenderGraph>	pRenderGraph;
	FRConstantBufferPtr<CbPrePass>		pCbPrePass;
	std::shared_ptr<dx12lib::ConstantBuffer> pCbFXAASetting;
};

}