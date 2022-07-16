#include "game.h"

#include "screen.h"

#include "utility/timer.h"
#include "utility/log.hpp"

bool Game::running = false;
static SDL_Color testRectColor = {0, 0, 0, 0xff};
static SDL_Rect testRect{.w = 12, .h = 12};

void Game::init() {
	running = true;
	std::thread gameLoop{run};
	gameLoop.detach();
}

void Game::run() {
	Timer timer;
	while (running) {
		timer.startCounting();

		SDL_PumpEvents(); // make sure we have the latest mouse state.
		SDL_GetMouseState(&testRect.x, &testRect.y);

		timer.syncThread(gameLoopPeriod);
	}
}

void Game::shutdown() {
	running = true;
}

void Game::render() {
	Screen::setDrawColor({0, 0, 0, 0xff});
	Screen::drawRect(testRect);
}