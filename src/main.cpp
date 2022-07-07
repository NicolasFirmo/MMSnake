int main() {
	if (int error = SDL_Init(SDL_INIT_VIDEO); error) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL (%d): %s\n", error,
					 SDL_GetError());
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("MMSnake", SDL_WINDOWPOS_UNDEFINED,
										  SDL_WINDOWPOS_UNDEFINED, 600, 480, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
		return 1;
	}
	if (int error = SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); error) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not set draw blend mode (%d): %s\n", error,
					 SDL_GetError());
		return 1;
	}

	std::cout << "MMSnake initialized!\n";

	SDL_SetRenderDrawColor(renderer, 0x40, 0x80, 0x10, 0x00);
	SDL_Event event;
	while (true) {
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);

		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			break;
	}
}