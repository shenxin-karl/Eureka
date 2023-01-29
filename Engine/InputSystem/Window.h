#pragma once
#include <windows.h>
#include <memory>
#include <string>
#include <functional>
#include "Foundation/ITick.h"

namespace Eureka {

class InputSystem;
class GameTimer;

class Window : public ITick {
public:
	class WindowClass;
	Window(int width, int height, const std::string &title, InputSystem *pInputSystem);
	Window(const Window &) = delete;
	Window &operator=(const Window &) = delete;
	bool shouldClose() const;
	void setShouldClose(bool flag);
	int getReturnCode() const;
	void setMessageDispatchCallback(const std::function<void(HWND, UINT, WPARAM, LPARAM)> &callback);
	void setPrepareMessageCallBack(const std::function<bool(HWND, UINT, WPARAM, LPARAM)> &callback);
	void setResizeCallback(const std::function<void(int x, int y)> &callback);
	int getWidth() const;
	int getHeight() const;
	HWND getHWND() const;
	float aspectRatio() const;
	const std::string &getTitle() const;
	void setShowTitle(const std::string &title);
	bool isPause() const;
	virtual void beginTick(std::shared_ptr<GameTimer> pGameTimer) override;
	void setCanPause(bool bPause);
	~Window() override;
private:
	static void centerWindow(HWND hwnd);
	static LRESULT CALLBACK handleMsgSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK handleMsgThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT handleMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void stop();
	void start();
private:
	HWND _hwnd;
	int	 _width;
	int	 _height;
	bool _shouldClose;
	int  _result;
	std::string _title;
	InputSystem *_pInputSystem = nullptr;
	std::function<void(HWND, UINT, WPARAM, LPARAM)> _messageDispatchCallback;
	std::function<bool(HWND, UINT, WPARAM, LPARAM)> _prepareMessageCallBack;
	std::function<void(int x, int y)>				_resizeCallback;
	std::shared_ptr<GameTimer>						_pGameTimer;
public:
	bool _canPause		  = true;
	bool _paused          = false;
	bool _minimized       = false;
	bool _maximized       = false;
	bool _fullScreenState = false;
	bool _resizeDirty     = false;
};

class Window::WindowClass {
	HINSTANCE hInstance_ = nullptr;
private:
	using HandleMessageFuncType = LRESULT (CALLBACK *)(HWND, UINT, WPARAM, LPARAM);
	static std::unique_ptr<WindowClass> _pSingleton;
public:
	WindowClass();
	~WindowClass();
	static HINSTANCE getInstance();
	static const wchar_t *getClassName();
	static inline HandleMessageFuncType pHandleMessageFunc = &(DefWindowProc);
};

}