#pragma once

#include "utility/vec.hpp"

class Screen {
public:
	static bool init(const char *title, const Vec2<int>& size);
	static void shutdown();

	static auto width() { return displayMode.w; }
	static auto height() { return displayMode.h; }
	static auto refreshRate() { return displayMode.refresh_rate; }

	static void setTitle(const char *title);

	static bool setDrawColor(const SDL_Color &color);
	static bool clear();

	static bool drawLine(const Vec2<int> &begin, const Vec2<int> &end);
	static bool drawRect(const SDL_Rect &rect);

	static void show();

private:
	static SDL_DisplayMode displayMode;
	static SDL_Window *window;
	static SDL_Renderer *renderer;
};