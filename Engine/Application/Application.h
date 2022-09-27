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
	void onInitialize(dx12lib::DirectContextProxy pDirectCtx);
	void onDestroy();
	void onBeginTick(std::shared_ptr<GameTimer> pGameTimer);
	void onTick(std::shared_ptr<GameTimer> pGameTimer);
	void onEndTick(std::shared_ptr<GameTimer> pGameTimer);
	void onResize(dx12lib::DirectContextProxy pDirectCtx, int width, int height);
protected:
	int  _width    = 800;
	int  _height   = 600;
	bool _canPause = true;
	size_t _fps    = 120;
	std::string _title = "Application";
	std::shared_ptr<dx12lib::Adapter>    _pAdapter;
	std::shared_ptr<dx12lib::Device>     _pDevice;
	std::shared_ptr<dx12lib::SwapChain>  _pSwapChain;
	std::shared_ptr<InputSystem>         _pInputSystem;
};

}
