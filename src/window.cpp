#include "window.h"

#include "app.h"

#include "events/mouse_event.h"
#include "events/window_size_event.h"

#include "utility/log.hpp"
#include "utility/tracer.h"

#include "core/assert.h"

GLFWwindow *Window::handle = nullptr;

Size2<GLsizei> Window::size{};
int Window::vsync{};

void Window::init(const char *title, const Size2<GLsizei> &size, const bool vsyncEnabled) {
	profileTrace();
	Window::size = size;

	glfwSetErrorCallback([](int error, const char *description) {
		fmt::print(stderr, "GLFW error ({}): {}", error, description);
	});

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_SAMPLES, 4);

	handle = glfwCreateWindow(size.w, size.h, title, NULL, NULL);
	glfwMakeContextCurrent(handle);
	debugAssert(handle, "Failed to create GLFW window");

	setVsync(vsyncEnabled);

	debugAssert(gladLoadGL((GLADloadfunc)glfwGetProcAddress),
				"Failed to initialize OpenGL context");

	debugLog("OpenGL info:\n");
	debugLog("\tVendor: {:s}\n", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
	debugLog("\tRenderer: {:s}\n", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
	debugLog("\tVersion: {:s}\n", reinterpret_cast<const char *>(glGetString(GL_VERSION)));

	glfwSetMouseButtonCallback(handle, mouseButtonCallback);
	glfwSetCursorPosCallback(handle, mouseMoveCallback);
	glfwSetWindowSizeCallback(handle, windowSizeCallback);
}

void Window::mouseButtonCallback(GLFWwindow * /*window*/, int button, int action, int mods) {
	App::onEvent(MouseButtonEvent{MouseButton(button), MouseAction(action), MouseMods(mods)});
}

void Window::mouseMoveCallback(GLFWwindow * /*window*/, double xpos, double ypos) {
	App::onEvent(MouseMoveEvent{
		{.x = xpos, .y = ypos}
	  });
}

void Window::windowSizeCallback(GLFWwindow * /*window*/, int width, int height) {
	App::onEvent(WindowSizeEvent{
		{.w = width, .h = height}
	 });
}

void Window::shutdown() {
	profileTrace();
	glfwTerminate();
}

bool Window::closing() {
	return glfwWindowShouldClose(handle);
}

void Window::showFrame() {
	profileTrace();
	glfwSwapBuffers(handle);
}

void Window::setVsync(bool enabled) {
	vsync = enabled ? 1 : 0;
	glfwSwapInterval(vsync);
}

void Window::pollEvents() {
	profileTrace();
	glfwPollEvents();
}

void Window::setTitle(const char *title) {
	glfwSetWindowTitle(handle, title);
}
