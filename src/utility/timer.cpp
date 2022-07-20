#include "timer.h"

void Timer::startCounting() {
	startTime_ = clock::now();
}
int64_t Timer::getMicrosecondsElapsed() const {
	return std::chrono::duration_cast<std::chrono::microseconds>(clock::now() - startTime_).count();
}
double Timer::getSecondsElapsed() const {
	static constexpr auto microsecondsTosecondsRatio = 1'000'000.0;
	return double(getMicrosecondsElapsed()) / microsecondsTosecondsRatio;
}

void Timer::syncThread(std::chrono::microseconds period) const {
	const auto elapsed = clock::now() - startTime_;
	const auto remaining = period - elapsed;
	std::this_thread::sleep_for(std::max(remaining.zero(), remaining));
}