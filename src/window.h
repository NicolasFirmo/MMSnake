#pragma once

#include "geometric/size.hpp"

class Window {
public:
	static void init(const char* title, const Size2<GLsizei>& size = {.w = 800, .h = 600},
					 bool vsyncEnabled = true);
	static void shutdown();

	static bool closing();

	static void pollEvents();

	static void showFrame();

	[[nodiscard]] static const auto& size() { return size_; }
	[[nodiscard]] static auto width() { return size_.w; }
	[[nodiscard]] static auto height() { return size_.h; }
	[[nodiscard]] static auto aspectRatio() { return double(size_.w) / size_.h; }

	static void setVsync(bool enabled);
	[[nodiscard]] static bool isVsyncOn() { return vsync_ != 0; }

	static void setTitle(const char* title);

private:
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
	static void windowSizeCallback(GLFWwindow* window, int width, int height);

	static Size2<GLsizei> size_;
	static int vsync_;

	static GLFWwindow* handle_;
};
