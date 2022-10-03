#pragma once
#include "Application/Application.h"

namespace Eureka {

class EurekaApplication : public Application {
public:
	void onInitialize(dx12lib::DirectContextProxy pDirectCtx) override;
	void onDestroy() override;
	void onBeginTick(std::shared_ptr<GameTimer> pGameTimer) override;
	void onTick(std::shared_ptr<GameTimer> pGameTimer) override;
	void onEndTick(std::shared_ptr<GameTimer> pGameTimer) override;
	void onResize(dx12lib::DirectContextProxy pDirectCtx, int width, int height) override;
};

}