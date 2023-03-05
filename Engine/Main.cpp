#include <iostream>
#include "Application/EurekaApplication.h"
#include "Foundation/GameTimer.h"
#include "Math/MathHelper.h"
#include <filesystem>

int main(int argc, char *argv[]) {
	try {
		auto pGameTimer = std::make_shared<Eureka::GameTimer>();
		Eureka::Application::Initialize(new Eureka::EurekaApplication);
		while (Eureka::Application::IsRunning()) {
			pGameTimer->startNewFrame();
			Eureka::Application::BeginTick(pGameTimer);
			Eureka::Application::Tick(pGameTimer);
			Eureka::Application::EndTick(pGameTimer);
		}
		Eureka::Application::Destroy();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		std::wstring message = dx12lib::to_wstring(e.what());
		MessageBox(nullptr, message.c_str(), L"Error", MB_OK | MB_ICONHAND);
	}
}
