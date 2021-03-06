#pragma once
#include "SDL.h"

class GameObject
{

public:
	GameObject(/*const char* texturePath*/);
	~GameObject();

	void OnSpawn(int xAxis, int yAxis, bool isAstorid);
	void Update();
	void Render();
	void ObjectMovement();

	float _xvelocity = 0;
	float _yvelocity = 0;
	float angle = 0;
	int windowSizeX = 0, windowSizeY = 0;

private:
	float _xpos;
	float _ypos;
	bool _isAstroid;

	SDL_Texture* _objTexture;
	SDL_Rect _srcRect;
	SDL_Rect _destRect;
};