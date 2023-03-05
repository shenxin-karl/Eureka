#pragma once
#include <Windows.h>
#include <DirectXMath.h>
#include <memory>
#include "Dx12lib/Device/Device.h"
#include "Dx12lib/Device/SwapChain.h"
#include "Dx12lib/dx12libStd.h"
#include "Dx12lib/Context/ContextProxy.hpp"
#include "InputSystem/InputSystem.h"

namespace Eureka {

namespace DX  = DirectX;
namespace WRL = Microsoft::WRL;
class InputSystem;
class GameTimer;

class Application : ITick {
public:
	Application() = default;
	Application(const Application &) = delete;
	Application &operator=(const Application &) = delete;
	~Application() override = default;
public:
	static void Initialize(Application *pApplication);
	static void BeginTick(std::shared_ptr<GameTimer> pGameTimer);
	static void Tick(std::shared_ptr<GameTimer> pGameTimer);
	static void EndTick(std::shared_ptr<GameTimer> pGameTimer);
	static void Destroy();
	static bool IsRunning();
	static auto getDevice() -> const std::shared_ptr<dx12lib::Device> &;
	static auto getSwapChain() -> const std::shared_ptr<dx12lib::SwapChain> &; 
	static auto getInputSystem() -> const std::shared_ptr<InputSystem> &;
public:
private:
	void initialize() override;
	void destroy() override;
	void beginTick(std::shared_ptr<GameTimer> pGameTimer) override;
	void tick(std::shared_ptr<GameTimer> pGameTimer) override;
	void endTick(std::shared_ptr<GameTimer> pGameTimer) override;
	void resize(int width, int height);
protected:
	virtual void onInitialize(dx12lib::DirectContextProxy pDirectCtx) {}
	virtual void onDestroy() {}
	virtual void onBeginTick(std::shared_ptr<GameTimer> pGameTimer) {}
	virtual void onTick(std::shared_ptr<GameTimer> pGameTimer) {}
	virtual void onEndTick(std::shared_ptr<GameTimer> pGameTimer) {}
	virtual void onResize(dx12lib::DirectContextProxy pDirectCtx, int width, int height) {}
protected:
	int									_width    = 1280;
	int									_height   = 760;
	bool								_canPause = true;
	size_t								_fps	  = 120;
	std::string							_title = "Eureka";
	std::shared_ptr<dx12lib::Adapter>   _pAdapter;
	std::shared_ptr<dx12lib::Device>    _pDevice;
	std::shared_ptr<dx12lib::SwapChain> _pSwapChain;
	std::shared_ptr<InputSystem>        _pInputSystem;
	static inline Application *			_inst;
};

}
