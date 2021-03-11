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
}

void GameObject::Render()
{
	SDL_RenderCopyEx(Game::renderer, _objTexture, &_srcRect, &_destRect, angle,	NULL, SDL_FLIP_NONE);
}

