#include <iostream>
#include <sol/sol.hpp>
#include "Application/EurekaApplication.h"
#include "GameTimer/GameTimer.h"
#include "Math/MathHelper.h"

struct uint2 {
	uint32_t x;
	uint32_t y;
	friend uint2 operator/(const uint2 &lhs, const uint32_t &rhs) {
		return { lhs.x / rhs, lhs.y / rhs };
	}
	friend uint2 operator%(const uint2 &lhs, const uint32_t &rhs) {
		return { lhs.x % rhs, lhs.y % rhs };
	}
};


#define CBDR_TILE_DIMENSION 64

uint2 CalcClusterTileParam(uint32_t renderTargetWidth, uint2 dispatchID, uint32_t zClusterSize) {
	uint32_t xTileSize = Math::MathHelper::divideByMultiple(renderTargetWidth, CBDR_TILE_DIMENSION);
	uint2 tileID = dispatchID / CBDR_TILE_DIMENSION;
	uint32_t startIndex = (tileID.y * xTileSize + tileID.x) * zClusterSize;
	uint2 groupID = dispatchID % CBDR_TILE_DIMENSION;
	uint32_t groupIndex = groupID.y * CBDR_TILE_DIMENSION + groupID.x;
	return uint2(startIndex, groupIndex);
}

void test() {
	uint32_t renderTargetWidth = 1280;
	uint2 dispatchID = { 65, 1 };
	CalcClusterTileParam(renderTargetWidth, dispatchID, 6);
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
