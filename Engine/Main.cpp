#include <iostream>
#include <sol/sol.hpp>
#include "Application/EurekaApplication.h"
#include "GameTimer/GameTimer.h"
#include "Math/MathHelper.h"


	using namespace Math;
Vector3 PackVelocity(Vector3 Velocity)
{
	// Stretch dx,dy from [-64, 63.875] to [-512, 511] to [-0.5, 0.5) to [0, 1)
	// Velocity.xy = (0,0) must be representable.
	return Velocity * Vector3(8, 8, 4096) / 1024.0 + 512 / 1023.0;
}

// Unpack the velocity from R10G10B10A2_UNORM
Vector3 UnpackVelocity(Vector3 Velocity)
{
	return (Velocity - 512.0 / 1023.0) * Vector3(1024, 1024, 2) / 8.0;
}

void test() {
	Vector3 v(91.f, 3.2f, 0.00064f);
	auto packed = PackVelocity(v);
	auto v1 = UnpackVelocity(packed);
}

int main() {
	test();

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
