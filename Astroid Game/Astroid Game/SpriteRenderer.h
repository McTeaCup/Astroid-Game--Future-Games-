#pragma once

#include "Components.h"
#include "SDL.h"

#include <iostream>

class SpriteRenderer : public Component
{
private:
	Transform* _transform;
	SDL_Texture* _texture;
	SDL_Rect _srcRect;
	SDL_Rect _dstRect;

public:
	float offsetAngle;
	
	SpriteRenderer() = default;
	SpriteRenderer(const char* path)
	{
		SetTexture(path);
		offsetAngle = 0;
	}
	SpriteRenderer(const char* path, float offsetAngle)
	{
		SetTexture(path);
		this->offsetAngle = offsetAngle;
	}
	
	~SpriteRenderer()
	{
		SDL_DestroyTexture(_texture);
	}

	void SetTexture(const char* path)
	{
		_texture = TextureManager::LoadTexture(path);
	}

	void Init() override
	{
		_transform = &entity->GetComponent<Transform>();

		int w = 0;
		int h = 0;
		SDL_QueryTexture(_texture, nullptr, nullptr, &w, &h);
		
		_srcRect.x = _srcRect.y = 0;
		_srcRect.w = _dstRect.w = w;
		_srcRect.h = _dstRect.h = h;
	}

	void Update() override
	{
		_dstRect.x = _transform->position.x() - _dstRect.w / 2;
		_dstRect.y = _transform->position.y() - _dstRect.h / 2;
	}

	void Draw() override
	{
		TextureManager::Draw(_texture, _srcRect, _dstRect, _transform->angle + offsetAngle);
	}
};
