#pragma once
#include "SDL.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* path, SDL_Renderer* renderer);
};

