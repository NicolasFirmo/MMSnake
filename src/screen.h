#pragma once

#include "utility/rect.hpp"
#include "utility/size.hpp"

class Screen {
public:
	static void init(const char *title, const Size2<GLsizei> &size = {.w = 800, .h = 600});
	static void shutdown();

	static void pollEvents();

	[[nodiscard]] static auto getWidth() { return size.w; }
	[[nodiscard]] static auto getHeight() { return size.h; }
	// TODO(Nicolas): get refresh rate

	static void setTitle(const char *title);

	static void setDrawColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	static void clear();

	static void drawRect(const Rect<GLfloat> &rect);

	static void show();

private:
	static Size2<GLsizei> size;
	static GLFWwindow *window;
};