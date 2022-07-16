#pragma once

class Game {
public:
	static constexpr auto gameLoopPeriod = std::chrono::microseconds(1'000'000 / 600);

	static void init();
	static void run();
	static void shutdown();

	static void render();

private:
	static bool running;
};