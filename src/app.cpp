#include "app.h"

#include "game.h"
#include "screen.h"

#include "utility/log.hpp"
#include "utility/timer.h"

bool App::running = false;

App::ExitCode App::init() {
	if (int error = SDL_Init(sdlInitFlags); error) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL (%d): %s\n", error,
					 SDL_GetError());
		shutdown();
		return ExitCode::applicationError;
	}

	if (!Screen::init("StickTheStick", {.w = 600, .h = 480})) {
		shutdown();
		return ExitCode::applicationError;
	}

	return ExitCode::success;
}

App::ExitCode App::run() {
	running = true;

	SDL_Color backgroundColor = {.r = 0x40, .g = 0x80, .b = 0x10, .a = 0xff};
	Screen::setDrawColor(backgroundColor);

	std::thread eventLoop{[&, event = SDL_Event{}]() mutable {
		while (SDL_WaitEvent(&event))
			onEvent(event);
	}};
	eventLoop.detach();

	Game::init();

	Timer timer;
	while (running) {
		debugLog("Frame rate: {:.1f}fps\n", 1 / timer.getCount());
		timer.startCounting();

		Screen::setDrawColor(backgroundColor);
		Screen::clear();

		Game::render();

		Screen::show();
	}

	Game::shutdown();

	return ExitCode::success;
}

void App::onEvent(SDL_Event event) {
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN: {
		Screen::setDrawColor({.r = 0xE0, .g = 0x10, .b = 0x10, .a = 0xff});
		Screen::setTitle("Ouch!");
		break;
	}
	case SDL_MOUSEBUTTONUP: {
		Screen::setDrawColor({.r = 0x40, .g = 0x80, .b = 0x10, .a = 0xff});
		Screen::setTitle("StickTheStick");
		break;
	}
	case SDL_MOUSEWHEEL: {
		Screen::setDrawColor({.r = 0xE0, .g = 0x10, .b = 0x80, .a = 0xff});
		Screen::setTitle("Nice!");
	}
	case SDL_KEYDOWN: {
		running = event.key.keysym.sym != SDLK_ESCAPE;
		break;
	}
	case SDL_WINDOWEVENT: {
		running = event.window.event != SDL_WINDOWEVENT_CLOSE;
		break;
	}
	}
}

void App::shutdown() {
	running = false;
	Screen::shutdown();
	SDL_Quit();
}