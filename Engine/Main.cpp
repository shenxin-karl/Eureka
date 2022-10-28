#include <iostream>
#include <sol/sol.hpp>
#include "Application/EurekaApplication.h"
#include "GameTimer/GameTimer.h"
#include "Math/MathHelper.h"



void test() {
	using namespace Math;
	Matrix4 matProj = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(45.f),
		1.f,
		0.1,
		1000.f
	);
	Matrix4 matView = DirectX::XMMatrixLookAtLH(
		Vector3(0.f, 0.f, 0.f), 
		Vector3(0.f, 0.f, 10.f), 
		Vector3(0.f, 1.f, 0.f)
	);

	Matrix4 matViewProj = matProj * matView;
	Matrix4 matViewport = Matrix4::makeScale(1280, 760, 1.0) * Matrix4::makeTranslation(0.5f, 0.5f, 0.f) * Matrix4::makeScale(0.5f, -0.5f, 1.f);

	
		Vector4 point(-5.f, 0.f, 5.f, 1.0);
		Vector4 res = matViewport * matViewProj * point;
		res /= res.w;
	
	
		point = Vector4(-5.f, 0.f, 5.f, 1.0);
		res = matViewProj * point;
		res /= res.w;
		res.xy = (Vector2(res.xy) * 0.5f).xy;
		res.xy = (Vector2(res.xy) + 0.5f).xy;
		res.x = res.x * 1280;
		res.y = res.y * 760;
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
