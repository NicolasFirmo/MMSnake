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