#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturPath, SDL_Renderer* renderer)
{
	_renderer = renderer;
	_objTexture = TextureManager::LoadTexture(texturPath, _renderer);
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	_xpos = 0;
	_ypos = 0;

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
	SDL_RenderCopy(_renderer, _objTexture, &_srcRect, &_destRect);
}
