#pragma once
#include <memory>

namespace Eureka {

class GameTimer;
class ITick {
public:
	virtual void initialize() {}
	virtual void destroy() {}
	virtual void beginTick(std::shared_ptr<GameTimer> pGameTimer) {}
	virtual void tick(std::shared_ptr<GameTimer> pGameTimer) {}
	virtual void endTick(std::shared_ptr<GameTimer> pGameTimer) {}
	virtual ~ITick() = default;
};

}