#pragma once

#include "utility/size.hpp"

class Window {
public:
	static void init(const char *title, const Size2<GLsizei> &size = {.w = 800, .h = 600},
					 bool vsyncEnabled = true);
	static void shutdown();

	static void pollEvents();

	static void showFrame();

	[[nodiscard]] static const auto &getSize() { return size; }
	[[nodiscard]] static auto getWidth() { return size.w; }
	[[nodiscard]] static auto getHeight() { return size.h; }

	[[nodiscard]] static void setVsync(bool enabled);
	[[nodiscard]] static bool isVsyncOn() { return vsync != 0; }

	static void setTitle(const char *title);

private:
	static GLFWwindow *handle;

	static Size2<GLsizei> size;
	static int vsync;
};