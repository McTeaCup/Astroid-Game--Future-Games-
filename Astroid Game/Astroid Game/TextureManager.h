#pragma once
#include "SDL.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* path);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, double angle);
};

