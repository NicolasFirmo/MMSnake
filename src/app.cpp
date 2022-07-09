#include "app.h"

#include "screen.h"

#include "utility/float-to-uint8.h"
#include "utility/timer.h"

bool App::running = false;

App::ExitCode App::init() {
	if (int error = SDL_Init(SDL_INIT_VIDEO); error) {
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

	std::thread eventLoop{[&]() {
		SDL_Event event;
		while (running && SDL_WaitEvent(&event)) {
			switch (event.type) {
			case SDL_MOUSEBUTTONDOWN: {
				Screen::setDrawColor({.r = 0xff, .g = 0x40, .b = 0x10, .a = 0xff});
				Screen::setTitle("Ouch!");
				break;
			}
			case SDL_MOUSEBUTTONUP: {
				Screen::setDrawColor(backgroundColor);
				Screen::setTitle("StickTheStick");
				break;
			}
			case SDL_KEYDOWN: {
				running = event.key.type != SDLK_ESCAPE;
				break;
			}
			}
		}
	}};

	Timer timer;
	while (running) {
		const auto deltaT = timer.getCount();
		timer.startCounting();

		Screen::clear();

		Screen::show();
	}
	eventLoop.join();

	shutdown();
	return ExitCode::success;
}

void App::shutdown() {
	Screen::shutdown();
	SDL_Quit();
}