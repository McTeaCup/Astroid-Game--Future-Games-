#pragma once
#include "SDL.h"

class GameObject
{

public:
	GameObject(const char* texturPath, SDL_Renderer* renderer);
	~GameObject();

	void Update();
	void Render();

private:
	int _xpos;
	int _ypos;

	SDL_Texture* _objTexture;
	SDL_Rect _srcRect;
	SDL_Rect _destRect;
	SDL_Renderer* _renderer;
};