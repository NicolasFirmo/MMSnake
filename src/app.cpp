#include "app.h"

#include "game.h"
#include "renderer/renderer.h"
#include "window.h"

#include "utility/log.hpp"
#include "utility/timer.h"

bool App::running = false;

App::ExitCode App::init() {
	Window::init("StickTheStick", {.w = 600, .h = 480});
	Renderer::init();
	Renderer::setViewport({.pos = {.x = 0, .y = 0}, .size = Window::getSize()});

	return ExitCode::success;
}

App::ExitCode App::run() {
	running = true;

	Game::init();

	Timer timer;
	while (running) {
		debugLog("Frame rate: {:.1f}fps\n", 1 / timer.getSecondsElapsed());
		timer.startCounting();

		Window::pollEvents();

		Renderer::setDrawColor(0x40 / 255.0F, 0x80 / 255.0F, 0x10 / 255.0F, 0xff / 255.0F);
		Renderer::clear();

		Game::render();

		Renderer::renderFrame();
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