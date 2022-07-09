#pragma once

class App {
public:
	enum class ExitCode { success = 0, applicationError };

	static ExitCode init();
	static ExitCode run();
	static void shutdown();

private:
	static void onEvent(SDL_Event event);

	static constexpr Uint32 sdlInitFlags = SDL_INIT_VIDEO;

	static bool running;
};