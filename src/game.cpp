#include "game.h"

#include "utility/log.hpp"
#include "utility/rect.hpp"
#include "utility/timer.h"
#include "utility/tracer.h"

bool Game::running = false;
static Rect<GLfloat> testRect{.size = {.w = 12, .h = 12}};

void Game::init() {
	profileTrace();
	running = true;
	std::thread gameLoop{run};
	gameLoop.detach();
}

void Game::run() {
	profileTrace();
	Timer timer;
	while (running) {
		profileTrace("game run loop");
		timer.startCounting();

		// TODO(Nicolas): pool mouse state with GLFW
		// SDL_GetMouseState(&testRect.x, &testRect.y);

		timer.syncThread(gameLoopPeriod);
	}
}

void Game::shutdown() {
	profileTrace();
	running = true;
}

void Game::render() {
	profileTrace();
}