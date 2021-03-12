#include "GameObject.h"
#include "TextureManager.h"
#include "ScreenWraping.h"
#include <iostream>
#include "Game.h"

GameObject::GameObject(/*const char* texturePath*/)
{
	//_objTexture = TextureManager::LoadTexture(texturePath);
}

GameObject::~GameObject()
{
}

void GameObject::OnSpawn(int xAxis, int yAxis, bool isAstroid)
{
	//If the object is an astroid, set right values
	if (isAstroid)
	{
		_objTexture = TextureManager::LoadTexture("Resources/meteorGrey_tiny1.png");
		std::cout << "created Astroid" << std::endl;
		
		//Set position and acceleration
		_xpos = 0;
		_ypos = 0;
		_xvelocity = rand() % 30;
		std::cout << "Astoid: x velocity = " << _xvelocity;
		_yvelocity = rand() % 20;
		std::cout << " and y velocity = " << _yvelocity << std::endl;

		//Set size of sprite
		_srcRect.h = 18;
		_srcRect.w = 18;
		_srcRect.x = 0;
		_srcRect.y = 0;

		_isAstroid = true;
	}

	//If the object is the player, set the right values
	else
	{
		_objTexture = TextureManager::LoadTexture("Resources/playerShip.png");
		std::cout << "created Player" << std::endl;
		
		//Set position and acceleration
		_xpos = xAxis / 2;
		_ypos = yAxis / 2;

		//Set size of sprite
		_srcRect.h = 75;
		_srcRect.w = 99;
		_srcRect.x = 0;
		_srcRect.y = 0;

		_isAstroid = false;
	}
}

void GameObject::Update()
{
	ObjectMovement();

	//ScreenWraping(windowSizeX, windowSizeY);
}

void GameObject::Render()
{
	SDL_RenderCopyEx(Game::renderer, _objTexture, &_srcRect, &_destRect, angle,	NULL, SDL_FLIP_NONE);
}

void GameObject::ObjectMovement()
{
	if (_isAstroid)	//Constant rotation speed of object
	{
		angle += 0.5f;
	}

	_xpos += _xvelocity;
	_ypos += _yvelocity;

	_destRect.x = _xpos;
	_destRect.y = _ypos;
	_destRect.w = _srcRect.w * 2;
	_destRect.h = _srcRect.h * 2;
}

/*
void GameObject::ScreenWraping(int Xscreen, int Yscreen)
{
#pragma region Y-AxisWraping
	//Teleports up
	if (_ypos + (_destRect.h / 2) > Yscreen)
	{
		_ypos = 0 - (_destRect.h / 2);
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
*/

