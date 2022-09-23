#include "window.h"

#include "app.h"

#include "events/mouse_event.h"
#include "events/window_size_event.h"

#include "utility/log.hpp"
#include "utility/tracer.h"

#include "core/assert.h"

GLFWwindow* Window::handle_ = nullptr;

Size2<GLsizei> Window::size_{};
int Window::vsync_{};

void Window::init(const char* title, const Size2<GLsizei>& size, const bool vsyncEnabled) {
	profileTraceFunc();

	size_ = size;

	glfwSetErrorCallback([](int error, const char* description) {
		fmt::print(stderr, "GLFW error ({}): {}", error, description);
	});

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_SAMPLES, 4);

	handle_ = glfwCreateWindow(size.w, size.h, title, NULL, NULL);
	glfwMakeContextCurrent(handle_);
	debugAssert(handle_, "Failed to create GLFW window");

	setVsync(vsyncEnabled);

	debugAssert(gladLoadGL((GLADloadfunc)glfwGetProcAddress),
				"Failed to initialize OpenGL context");

	debugLog("OpenGL info:\n");
	debugLog("\tVendor: {:s}\n", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	debugLog("\tRenderer: {:s}\n", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	debugLog("\tVersion: {:s}\n", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

	glfwSetMouseButtonCallback(handle_, mouseButtonCallback);
	glfwSetCursorPosCallback(handle_, mouseMoveCallback);
	glfwSetWindowSizeCallback(handle_, windowSizeCallback);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	auto& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(handle_, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void Window::shutdown() {
	profileTraceFunc();

	glfwTerminate();
}

bool Window::closing() {
	return glfwWindowShouldClose(handle_) == 0 ? false : true;
}

void Window::pollEvents() {
	profileTraceFunc();

	glfwPollEvents();
}

void Window::showFrame() {
	profileTraceFunc();

	glfwSwapBuffers(handle_);
}

void Window::setVsync(bool enabled) {
	vsync_ = enabled ? 1 : 0;
	glfwSwapInterval(vsync_);
}

void Window::setTitle(const char* title) {
	glfwSetWindowTitle(handle_, title);
}

void Window::mouseButtonCallback(GLFWwindow* /*window*/, int button, int action, int mods) {
	App::onEvent(MouseButtonEvent{MouseButton(button), MouseAction(action), MouseMods(mods)});
}

void Window::mouseMoveCallback(GLFWwindow* /*window*/, double xpos, double ypos) {
	App::onEvent(MouseMoveEvent{{.x = xpos, .y = ypos}});
}

void Window::windowSizeCallback(GLFWwindow* /*window*/, int width, int height) {
	size_ = {.w = width, .h = height};
	App::onEvent(WindowSizeEvent{{.w = width, .h = height}});
}
