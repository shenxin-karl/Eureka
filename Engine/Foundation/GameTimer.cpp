#include "GameTimer.h"

namespace Eureka {

GameTimer::GameTimer() {
	reset();
}

void GameTimer::reset() {
	baseTime_ = chrono::steady_clock::now();
	prevTime_ = baseTime_;
	stopped_ = false;
	deltaTime_ = 0.f;
	totalTime_ = 0.f;
	pausedTime_ = 0.f;
	prevFrameTimes_ = 30;
	currFameTimes_ = 0;
	nextTime_ = std::chrono::system_clock::to_time_t(chrono::system_clock::now()) + 1;
	newSeconds_ = false;
}

void GameTimer::start() {
	if (!stopped_)
		return;

	stopped_ = false;
	auto currTime = chrono::steady_clock::now();
	prevTime_ = currTime;
	chrono::duration<float> diff = currTime - stoppedTime_;
	pausedTime_ += diff.count();
}

void GameTimer::stop() {
	if (stopped_)
		return;

	deltaTime_ = 0.f;
	stopped_ = true;
	stoppedTime_ = chrono::steady_clock::now();
}

void GameTimer::startNewFrame() {
	if (stopped_)
		return;

	auto currTime = chrono::steady_clock::now();
	chrono::duration<float> diff = currTime - prevTime_;
	prevTime_ = currTime;
	deltaTime_ = diff.count();
	diff = currTime - baseTime_;
	totalTime_ = diff.count() - pausedTime_;
	++currFameTimes_;
	time_t sysTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
	newSeconds_ = false;
	if (sysTime >= nextTime_) {
		nextTime_ = sysTime + 1;
		prevFrameTimes_ = currFameTimes_;
		currFameTimes_ = 0;
		newSeconds_ = true;
	}
}

float GameTimer::getTotalTime() const {
	return totalTime_;
}

float GameTimer::getDeltaTime() const {
	return deltaTime_;
}

std::uint32_t GameTimer::FPS() const {
	return prevFrameTimes_;
}

float GameTimer::mspf() const {
	return 1000.f / float(FPS());
}

bool GameTimer::oneSecondTrigger() const {
	return newSeconds_;
}

}