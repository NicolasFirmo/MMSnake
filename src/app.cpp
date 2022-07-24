#include "app.h"

#include "game.h"
#include "window.h"

#include "renderer/renderer.h"
#include "renderer/shader.h"

#include "utility/log.hpp"
#include "utility/timer.h"
#include "utility/tracer.h"

bool App::running = false;

App::ExitCode App::init() {
	Window::init("StickTheStick", {.w = 600, .h = 480});
	Renderer::init();
	Renderer::setViewport({
		.pos = {				.x = 0,				.y = 0},
			 .size = {Window::getHeight(), Window::getHeight()}
	   });

	return ExitCode::success;
}

App::ExitCode App::run() {
	running = true;

	Game::init();

	Shader shader{"line"};
	shader.bind();

	Timer timer;
	GLfloat timeWatch = 0.0F;
	while (running && !Window::closing()) {
		auto t = Tracer::trace();
		const auto deltaT = timer.getSecondsElapsed();
		debugLog("Frame rate: {:.1f}fps\n", 1 / deltaT);
		timeWatch += deltaT;
		timer.startCounting();

		Window::pollEvents();

		Renderer::setDrawColor(1.0F, 1.0F, 1.0F, 1.0F);
		Renderer::clear();

		Renderer::beginBatch();

		static constexpr auto pi = std::numbers::pi_v<GLfloat>;

		for (size_t i = 0; i < 50; ++i)
			Renderer::drawLine({.x = 0, .y = 0},
							   {.x = 0.4F * std::cos(timeWatch + i / 50.0F * 2 * pi),
								.y = 0.4F * std::sin(timeWatch + i / 50.0F * 2 * pi)},
							   0.020F - i / 50.0F * 0.015F);

		Renderer::endBatch();

		Window::showFrame();
	}

	Game::shutdown();

	shutdown();
	return ExitCode::success;
}

// TODO(Nicolas): set event callbacks in GLFW
// void App::onEvent(SDL_Event event) {
// 	switch (event.type) {
// 	case SDL_MOUSEBUTTONDOWN: {
// 		Screen::setDrawColor({.r = 0xE0, .g = 0x10, .b = 0x10, .a = 0xff});
// 		Screen::setTitle("Ouch!");
// 		break;
// 	}
// 	case SDL_MOUSEBUTTONUP: {
// 		Screen::setDrawColor({.r = 0x40, .g = 0x80, .b = 0x10, .a = 0xff});
// 		Screen::setTitle("StickTheStick");
// 		break;
// 	}
// 	case SDL_MOUSEWHEEL: {
// 		Screen::setDrawColor({.r = 0xE0, .g = 0x10, .b = 0x80, .a = 0xff});
// 		Screen::setTitle("Nice!");
// 	}
// 	case SDL_KEYDOWN: {
// 		running = event.key.keysym.sym != SDLK_ESCAPE;
// 		break;
// 	}
// 	case SDL_WINDOWEVENT: {
// 		running = event.window.event != SDL_WINDOWEVENT_CLOSE;
// 		break;
// 	}
// 	}
// }

void App::shutdown() {
	running = false;
	Window::shutdown();
}