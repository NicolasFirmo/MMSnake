#pragma once

class Game {
public:
	static void init();
	static void run();
	static void shutdown();

	static void render();

private:
	static bool running;
};