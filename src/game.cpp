#include "game.h"

#include "window.h"

#include "events/mouse_event.h"

#include "renderer/renderer.h"

#include "utility/log.hpp"
#include "utility/point.hpp"
#include "utility/timer.h"
#include "utility/tracer.h"

bool Game::running = false;
static Point2<GLfloat> cursorPosition{.x = .0F, .y = .0F};

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
		const auto deltaT = timer.getSecondsElapsed();
		timer.startCounting();
		debugLog("Game loop period: {}\n", deltaT);
		timer.syncThread(gameLoopPeriod);
	}
}

void Game::shutdown() {
	profileTrace();
	running = false;
}

void Game::onEvent(Event &evt) {
	auto type = evt.getType();

	switch (type) {
	case Event::Type::mouseMove: {
		const auto [screenX, screenY] = static_cast<MouseMoveEvent &>(evt).pos;

		cursorPosition.x = GLfloat(screenX / Window::getWidth() * 2) - 1.0F;
		cursorPosition.y = GLfloat(-screenY / Window::getHeight() * 2) + 1.0F;
		break;
	}
	default:
		break;
	}
}

void Game::render() {
	profileTrace();
	Renderer::beginBatch();

	for (size_t i = 0; i < 2; ++i)
		for (size_t j = 0; j < 2; ++j) {
			const Point2<GLfloat> corner = {.x = -.5F + i * 1.0F, .y = -.5F + j * 1.0F};
			Renderer::drawLine(corner, cursorPosition, .005F);
		}

	Renderer::endBatch();
}