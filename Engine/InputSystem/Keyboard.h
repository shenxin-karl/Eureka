#pragma once
#define NOMINMAX
#include <windows.h>
#include <bitset>
#include <queue>
#include "ITick/ITick.h"

namespace Eureka {

	enum class KeyState : int {
		Pressed,
		Released,
		Invalid,
	};

	struct CharEvent {
		CharEvent() = default;
		CharEvent(KeyState state, unsigned char character);
		unsigned char getCharacter() const;
		KeyState getState() const;
		bool isPressed() const;
		bool isInvalid() const;
		explicit operator bool() const;
	private:
		KeyState		_state = KeyState::Invalid;
		unsigned char	_character = 0;
	};

	struct KeyEvent {
		KeyEvent() = default;
		KeyEvent(KeyState state, unsigned char key);
		unsigned char getKey() const;
		KeyState getState() const;
		bool isPressed() const;
		bool isReleased() const;
		bool isInvalid() const;
		explicit operator bool() const;
	private:
		KeyState      _state = KeyState::Invalid;
		unsigned char _key = 0;				// Use the window's virtual button
	};

class GameTimer;
class Keyboard : public ITick {

public:
	static constexpr int kMaxKeyCodeSize = 0xff;
	static constexpr int kMaxQueueSize = 0xff;
	std::bitset<kMaxKeyCodeSize>	_keyState;
	std::bitset<kMaxKeyCodeSize>	_characterState;
	std::queue<KeyEvent>			_keycodeQueue;
	std::queue<CharEvent>			_characterQueue;
public:
	Keyboard();
	Keyboard(const Keyboard &) = delete;
	Keyboard &operator=(const Keyboard &) = delete;
	bool isKeyPressed(unsigned char key) const;
	bool isCharPressed(unsigned char key) const;
	/// https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	KeyEvent getKeyEvent();
	CharEvent getCharEvent();

	template<typename T>
	static void tryDiscardEvent(std::queue<T> &queue);

	void handleMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void endTick(std::shared_ptr<GameTimer> pGameTimer) override;
};


template<typename T>
void Keyboard::tryDiscardEvent(std::queue<T> &queue) {
	while (queue.size() > Keyboard::kMaxQueueSize)
		queue.pop();
}

}