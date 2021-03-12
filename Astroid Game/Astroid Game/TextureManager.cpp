#include "TextureManager.h"
#include "SDL_image.h"
#include "Game.h"

SDL_Texture* TextureManager::LoadTexture(const char* path)
{
	SDL_Surface* tempSurface = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dst);
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, double angle)
{
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dst, angle, nullptr, SDL_FLIP_NONE);
}
