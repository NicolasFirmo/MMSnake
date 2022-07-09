#include "screen.h"

SDL_DisplayMode Screen::displayMode{};
SDL_Window *Screen::window = nullptr;
SDL_Renderer *Screen::renderer = nullptr;

bool Screen::init(const char *title, const Vec2<int>& size) {
	if (int error = SDL_GetCurrentDisplayMode(0, &displayMode); error) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not get display mode (%d): %s\n", error,
					 SDL_GetError());
		shutdown();
		return false;
	}
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  size.w, size.h, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		shutdown();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
		shutdown();
		return false;
	}
	if (int error = SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); error) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not set draw blend mode (%d): %s\n", error,
					 SDL_GetError());
		shutdown();
		return false;
	}

	return true;
}
void Screen::shutdown() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

bool Screen::setDrawColor(const SDL_Color &color) {
	const auto &[r, g, b, a] = color;
	if (int error = SDL_SetRenderDrawColor(renderer, r, g, b, a); error) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not set clear color (%d): %s\n", error,
					 SDL_GetError());
	std::cerr << "erro";
		shutdown();
		return false;
	}

	return true;
}

bool Screen::clear() {
	if (int error = SDL_RenderClear(renderer); error) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not clear screen (%d): %s\n", error,
					 SDL_GetError());
		shutdown();
		return false;
	}
	return true;
}

bool Screen::drawLine(const Vec2<int> &begin, const Vec2<int> &end) {
	if (int error = SDL_RenderDrawLine(renderer, begin.x, begin.y, end.x, end.y); error) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not draw line (%d): %s\n", error,
					 SDL_GetError());
		shutdown();
		return false;
	}
	return true;
}

void Screen::setTitle(const char *title) {
	SDL_SetWindowTitle(window, title);
}

void Screen::show() {
	SDL_RenderPresent(renderer);
}