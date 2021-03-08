#include "SDL.h"

class App
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	window = SDL_CreateWindow("New Widow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, false);
};
