#include "app.h"

#include "game/game.h"
#include "window.h"

#include "renderer/renderer.h"
#include "renderer/shader.h"

#include "events/mouse_event.h"
#include "events/window_size_event.h"

#include "utility/log.hpp"
#include "utility/timer.h"
#include "utility/tracer.h"

#include "core/sleeper.h"

bool App::running = false;

App::ExitCode App::init() {
	profileTraceFunc();

	Window::init("StickTheStick", {.w = 600, .h = 480});
	Renderer::init();
	Renderer::setViewport({
		.pos = {.x = 0, .y = 0},
			 .size = Window::getSize()
	  });

	Sleeper::init();

	return ExitCode::success;
}

App::ExitCode App::run() {
	profileTraceFunc();

	running = true;
	{
		Shader shader{"line"};
		shader.bind();

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
				GLFWwindow *backup_current_context = glfwGetCurrentContext();
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

void App::onEvent(Event &&evt) {
	debugLog("app: {}\n", evt);

	Game::onEvent(evt);
}
