#include "game.h"

#include "screen.h"

#include "utility/timer.h"

bool Game::running = false;
static SDL_Color testRectColor = {0, 0, 0, 0xff};
static SDL_Rect testRect{.w = 12, .h = 12};

void Game::init() {
	running = true;
	std::thread gameLoop{run};
	gameLoop.detach();
}

void Game::run() {
	// Timer timer;
	while (running) {
		// const auto deltaT = timer.getCount();
		// timer.startCounting();

		SDL_GetMouseState(&testRect.x, &testRect.y);
	}
}

void Game::shutdown() {
	running = true;
}

void Game::render() {
	Screen::setDrawColor({0, 0, 0, 0xff});
	Screen::drawRect(testRect);
}