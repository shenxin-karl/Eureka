#include <iostream>
#include <sol/sol.hpp>
#include "Application/EurekaApplication.h"
#include "GameTimer/GameTimer.h"
#include "Math/MathHelper.h"

int main() {
	Eureka::EurekaApplication app;
	try {
		auto pGameTimer = std::make_shared<Eureka::GameTimer>();
		app.initialize();
		while (app.isRunning()) {
			pGameTimer->startNewFrame();
			app.beginTick(pGameTimer);
			app.tick(pGameTimer);
			app.endTick(pGameTimer);
		}
		app.destroy();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		MessageBox(nullptr, e.what(), "Error", MB_OK | MB_ICONHAND);
	}
}
