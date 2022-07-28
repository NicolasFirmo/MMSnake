#pragma once

#include "stick_figure.h"

#include "events/event.h"

class Game {
public:
	static constexpr auto gameLoopPeriod = std::chrono::microseconds(1'000'000 / 600);

	static void init();
	static void shutdown();

	static void onEvent(Event &evt);

	static void onImGui();

	static void render();

	static void drawStickFigure(const StickFigure &stickFigure);

private:
	static void run();

	static bool running;
};