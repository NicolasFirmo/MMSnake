#include "sleeper_windows.h"

#include "core/assert.h"

#include "timeapi.h"

void Sleeper::init() {
	timeBeginPeriod(1);
}

Sleeper::Sleeper() {
	debugAssert((timer_ = CreateWaitableTimer(NULL, TRUE, NULL)),
				"Unable to create waitable timer for Sleeper! (Windows)");
}

Sleeper::~Sleeper() {
	CloseHandle(timer_);
}

void Sleeper::sleep(int64_t microseconds) {
	LARGE_INTEGER li{0};
	li.QuadPart = static_cast<LONGLONG>(-microseconds * 10);

	debugAssert(SetWaitableTimer(timer_, &li, 0, NULL, NULL, FALSE),
				"Unable to set waitable timer for Sleeper! (Windows)");

	WaitForSingleObject(timer_, INFINITE);
}
