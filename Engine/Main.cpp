#include <iostream>
#include "Application/EurekaApplication.h"
#include "Foundation/GameTimer.h"
#include "Math/MathHelper.h"
#include <filesystem>

using namespace Eureka;

int main(int argc, char *argv[]) {
	try {
		auto pGameTimer = std::make_shared<GameTimer>();
		Application::Initialize(new EurekaApplication);
		while (Application::IsRunning()) {
			pGameTimer->startNewFrame();
			Application::BeginTick(pGameTimer);
			Application::Tick(pGameTimer);
			Application::EndTick(pGameTimer);
		}
		Application::Destroy();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		std::wstring message = dx12lib::to_wstring(e.what());
		MessageBox(nullptr, message.c_str(), L"Error", MB_OK | MB_ICONHAND);
	}
}
