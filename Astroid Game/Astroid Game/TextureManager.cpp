#include "TextureManager.h"
#include "SDL_image.h"

SDL_Texture* TextureManager::LoadTexture(const char* path, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}
