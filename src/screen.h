#pragma once

#include "utility/rect.hpp"
#include "utility/size.hpp"
#include "utility/vec.hpp"

class Screen {
public:
	static bool init(const char *title, const Size2<GLsizei> &size = {.w = 800, .h = 600});
	static void shutdown();

	static void pollEvents();

	static auto getWidth() { return size.w; }
	static auto getHeight() { return size.h; }
	// static auto refreshRate() { return displayMode.refresh_rate; }

	static void setTitle(const char *title);

	static void setDrawColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	static void clear();

	static void drawRect(const Rect<GLfloat> &rect);

	static void show();

private:
	static Size2<GLsizei> size;

	static GLFWwindow *window;
};