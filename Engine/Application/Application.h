#pragma once
#define  NOMINMAX
#include <Windows.h>
#include <DirectXMath.h>
#include "dx12lib/dx12libStd.h"
#include "dx12lib/Context/ContextProxy.hpp"
#include "InputSystem/InputSystem.h"



namespace Eureka {

namespace DX  = DirectX;
namespace WRL = Microsoft::WRL;
class InputSystem;
class GameTimer;

class Application : public ITick {
public:
	Application() = default;
	Application(const Application &) = delete;
	Application &operator=(const Application &) = delete;
	~Application() override = default;
	void initialize() final;
	void destroy() final;
	void beginTick(std::shared_ptr<GameTimer> pGameTimer) final;
	void tick(std::shared_ptr<GameTimer> pGameTimer) final;
	void endTick(std::shared_ptr<GameTimer> pGameTimer) final;
	void resize(int width, int height);
	bool isRunning() const;
protected:
	virtual void onInitialize(dx12lib::DirectContextProxy pDirectCtx) {}
	virtual void onDestroy() {}
	virtual void onBeginTick(std::shared_ptr<GameTimer> pGameTimer) {}
	virtual void onTick(std::shared_ptr<GameTimer> pGameTimer) {}
	virtual void onEndTick(std::shared_ptr<GameTimer> pGameTimer) {}
	virtual void onResize(dx12lib::DirectContextProxy pDirectCtx, int width, int height) {}
protected:
	int  _width    = 1280;
	int  _height   = 760;
	bool _canPause = true;
	size_t _fps    = 120;
	std::string _title = "Eureka";
	std::shared_ptr<dx12lib::Adapter>    _pAdapter;
	std::shared_ptr<dx12lib::Device>     _pDevice;
	std::shared_ptr<dx12lib::SwapChain>  _pSwapChain;
	std::shared_ptr<InputSystem>         _pInputSystem;
};

}
