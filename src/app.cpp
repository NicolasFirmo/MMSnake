#include "app.h"

#include "game.h"
#include "window.h"

#include "renderer/renderer.h"
#include "renderer/shader.h"

#include "events/mouse_event.h"
#include "events/window_size_event.h"

#include "utility/log.hpp"
#include "utility/timer.h"
#include "utility/tracer.h"

bool App::running = false;

App::ExitCode App::init() {
	profileTrace();
	Window::init("StickTheStick", {.w = 600, .h = 480});
	Renderer::init();
	Renderer::setViewport({
		.pos = {.x = 0, .y = 0},
			 .size = Window::getSize()
	  });

	return ExitCode::success;
}

App::ExitCode App::run() {
	profileTrace();
	running = true;

	Shader shader{"line"};
	shader.bind();

	Game::init();

	using namespace std::chrono;
	while (running && !Window::closing()) {
		profileTrace("app run loop");
		Window::pollEvents();

		Renderer::setDrawColor(1.0F, 1.0F, 1.0F, 1.0F);
		Renderer::clear();

		Game::render();

		Window::showFrame();
	}

	Game::shutdown();

	shutdown();
	return ExitCode::success;
}

void App::shutdown() {
	profileTrace();
	running = false;
	Renderer::shutdown();
	Window::shutdown();
}

static constexpr auto eventLogColor = fmt::fg(fmt::color::light_green);
void App::onEvent(Event &&evt) {
	auto type = evt.getType();

	switch (type) {
	case Event::Type::windowSize: {
		auto &[width, height] = static_cast<WindowSizeEvent &>(evt).size;
		fmt::print(eventLogColor, "Window size: {}x{}\n", width, height);
		break;
	}
	case Event::Type::mouseButton: {
		auto &[button, action, mods] = static_cast<MouseButtonEvent &>(evt);
		fmt::print(eventLogColor, "{} mouse button {}{}{}{}{}\n",
				   button == MouseButton::left	 ? "Left" :
				   button == MouseButton::right	 ? "Right" :
				   button == MouseButton::middle ? "Middle" :
												   "Unknown",
				   action == MouseAction::pressed ? "pressed" : "released",
				   mods != MouseMods::none ? " while holding " : "",
				   mods & MouseMods::shift && mods & MouseMods::ctrlAlt ? "shift+" :
				   mods & MouseMods::shift								? "shift" :
																		  "",
				   mods & MouseMods::ctrl && mods & MouseMods::alt ? "ctrl+" :
				   mods & MouseMods::ctrl						   ? "ctrl" :
																	 "",
				   mods & MouseMods::alt ? "alt" : "");
		break;
	}
	}

	Game::onEvent(evt);
}
