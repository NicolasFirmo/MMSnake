#include "game.h"

#include "utility/log.hpp"
#include "utility/rect.hpp"
#include "utility/timer.h"

bool Game::running = false;
static Rect<GLfloat> testRect{.size = {.w = 12, .h = 12}};

void Game::init() {
	running = true;
	std::thread gameLoop{run};
	gameLoop.detach();
}

void Game::run() {
	Timer timer;
	while (running) {
		timer.startCounting();

		// TODO(Nicolas): pool mouse state with GLFW
		// SDL_GetMouseState(&testRect.x, &testRect.y);

		timer.syncThread(gameLoopPeriod);
	}
}

void Game::shutdown() {
	running = true;
}

void Game::render() {
}