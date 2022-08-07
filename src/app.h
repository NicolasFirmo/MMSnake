#pragma once

#include "events/event.h"

#include "renderer/shader.h"

class App {
public:
	enum class ExitCode {
		success = 0,
		applicationError
	};

	static ExitCode init();
	static ExitCode run();
	static void shutdown();

	static void onEvent(Event&& evt);

private:
	static bool running;

	static Shader lineShader;
};