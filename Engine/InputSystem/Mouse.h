#pragma once
#define  NOMINMAX
#include <queue>
#include <Windows.h>
#include <bitset>
#include "ITick/ITick.h"

namespace Eureka {

class InputSystem;

enum class MouseState : int {
	LPress,
	LRelease,
	RPress,
	RRelease,
	WheelDown,
	WheelUp,
	Move,
	Wheel,
	Invalid,
	MaxCount,
};

struct MouseEvent {
	bool isLPress() const { return _state == MouseState::LPress; }
	bool isLRelease() const { return _state == MouseState::LRelease; }
	bool isRPress() const { return _state == MouseState::RPress; }
	bool isRRelease() const { return _state == MouseState::RRelease; }
	bool isWheelDown() const { return _state == MouseState::WheelDown; }
	bool isWheelUp() const { return _state == MouseState::WheelUp; }
	bool isMove() const { return _state == MouseState::Move; }
	bool isWheel() const { return _state == MouseState::Wheel; }
	bool isInvalid() const { return _state == MouseState::Invalid; }
	explicit operator bool() const;
public:
	int		    x = 0;
	int		    y = 0;
	MouseState	_state = MouseState::Invalid;
	float	    _offset = 0;
};

class GameTimer;
class Mouse : public ITick {
public:
	Mouse(InputSystem *pInputSystem);
	Mouse(const Mouse &) = delete;
	Mouse &operator=(const Mouse &) = delete;
	~Mouse() = default;
	void handleMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void endTick(std::shared_ptr<GameTimer> pGameTimer) override;
	MouseEvent getEvent();
	bool getShowCursor() const;
	void setShowCursor(bool bShow);
	void adjustCursorPosition();
	POINT getCursorPosition() const;
private:
	static constexpr size_t kEventMaxSize = 0xff;
	POINT _windowCenter;
	POINT _virtualCursorPos;
	POINT _lastCursorPos;
	bool _showCursor = true;
	InputSystem *_pInputSystem = nullptr;
	std::queue<MouseEvent> _events;
};

}