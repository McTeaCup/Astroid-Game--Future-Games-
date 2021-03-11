#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>

#include "Game.h"


GameObject::GameObject(const char* texturePath)
{
	_objTexture = TextureManager::LoadTexture(texturePath);
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	_xpos += _xvelocity;
	_ypos += _yvelocity;

	_srcRect.h = 75;
	_srcRect.w = 99;
	_srcRect.x = 0;
	_srcRect.y = 0;

	_destRect.x = _xpos;
	_destRect.y = _ypos;
	_destRect.w = _srcRect.w * 2;
	_destRect.h = _srcRect.h * 2;

	ScreenWraping(800, 600);
}

void GameObject::Render()
{
	SDL_RenderCopyEx(Game::renderer, _objTexture, &_srcRect, &_destRect, angle,	NULL, SDL_FLIP_NONE);
}

void GameObject::ScreenWraping(int Xscreen, int Yscreen)
{
#pragma region Y-AxisWraping
	//Teleports up
	if (_ypos + (_destRect.h / 2) > Yscreen)
	{
		_ypos = 0 - (_destRect.h / 2);
		std::cout << _ypos << std::endl;
	}

	if (_ypos + (_destRect.h / 2) < 0)
	{
		_ypos = Yscreen - (_destRect.h / 1.5);
	}
#pragma endregion

#pragma region X-AxisWraping
	//Teleports left
	if (_xpos + (_destRect.w / 2) > Xscreen)
	{
		_xpos = 0 - (_destRect.w / 2);
	}

	//Teleports right
	if (_xpos + (_destRect.w / 2) < 0)
	{
		_xpos = Xscreen - (_destRect.w / 2);
	}
#pragma endregion
}

