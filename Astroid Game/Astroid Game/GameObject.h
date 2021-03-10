#pragma once
#include "SDL.h"

class GameObject
{

public:
	GameObject(const char* texturPath, SDL_Renderer* renderer);
	~GameObject();

	void Update();
	void Render();
	void Rotate(float angle);
	
	float _xvelocity = 0;
	float _yvelocity = 0;
	float angle = 0;

private:
	float _xpos;
	float _ypos;


	SDL_Texture* _objTexture;
	SDL_Rect _srcRect;
	SDL_Rect _destRect;
	SDL_Renderer* _renderer;
};