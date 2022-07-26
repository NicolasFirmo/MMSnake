#pragma once

#include "events/event.h"

class Game {
public:
	static constexpr auto gameLoopPeriod = std::chrono::microseconds(1'000'000 / 600);

	static void init();
	static void shutdown();

	static void onEvent(Event &evt);

	static void render();

private:
	static void run();

	static bool running;
};