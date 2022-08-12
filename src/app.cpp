#include "app.h"

#include "game/game.h"
#include "window.h"

#include "renderer/renderer.h"

#include "events/mouse_event.h"
#include "events/window_size_event.h"

#include "utility/log.hpp"
#include "utility/timer.h"
#include "utility/tracer.h"

#include "core/sleeper.h"

bool App::running = false;

Shader App::lineShader;

App::ExitCode App::init() {
	profileTraceFunc();

	Window::init("StickTheStick", {.w = 600, .h = 480});
	Renderer::init();
	Renderer::setViewport({.size = Window::size()});

	lineShader = {"line"};
	lineShader.bind();

	resizeView(Window::size());

	Sleeper::init();

	return ExitCode::success;
}

App::ExitCode App::run() {
	profileTraceFunc();

	running = true;
	{
		Game::init();

		using namespace std::chrono;
		while (running && !Window::closing()) {
			profileTraceScope("app run loop");
			Window::pollEvents();

			Renderer::setDrawColor(1.0F, 1.0F, 1.0F, 1.0F);
			Renderer::clear();

			Game::render();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			Game::onImGui();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

			Window::showFrame();
		}

		Game::shutdown();
	}

	shutdown();
	return ExitCode::success;
}

void App::shutdown() {
	profileTraceFunc();

	running = false;
	Renderer::shutdown();
	Window::shutdown();
}

void App::onEvent(Event&& evt) {
	debugLog("app: {}\n", evt);

	auto type = evt.getType();

	switch (type) {
	case Event::Type::windowSize: {
		resizeView(static_cast<WindowSizeEvent&>(evt).size);
		break;
	}
	case Event::Type::mouseButton: {
		break;
	}
	case Event::Type::mouseMove: {
		break;
	}
	default: break;
	}

	Game::onEvent(evt);
}

void App::resizeView(const Size2<GLsizei>& size) {
	Renderer::setViewport({.size = size});
	const auto aspectRatio = GLfloat(size.w) / size.h;
	const auto projection  = Matrix4<GLfloat>::orthographic(-aspectRatio, aspectRatio, -1.0F, 1.0F);
	lineShader.setUniformMatrix4("u_ViewProjection", projection);
}