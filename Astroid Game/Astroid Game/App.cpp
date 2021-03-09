#include "App.h"
#include "TextureManager.h"

#include <iostream>

App::App()
{
}

App::~App()
{
}

SDL_Rect destRect;


void App::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
		_isRunning = false;
		return;
	}
	std::cout << "Subsystems initialised." << std::endl;

	SDL_Window* window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (window == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		_isRunning = false;
		return;
	}
	std::cout << "Window created." << std::endl;

	_renderer = SDL_CreateRenderer(window, -1, 0);
	if (_renderer == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		_isRunning = false;
		return;
	}
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	std::cout << "Renderer created." << std::endl;

	//Temp stuff for testing image loading.
	_playerTexture = TextureManager::LoadTexture("Resources/playerShip.png", _renderer);
	destRect.h = 75;
	destRect.w = 99;
	destRect.x = width / 2;
	destRect.y = height / 2;

	_isRunning = true;
}

void App::HandleEvents()
{
	SDL_Event SDLevent;

	while (SDL_PollEvent(&SDLevent))
	{
		if (SDLevent.type == SDL_QUIT)
		{
			_isRunning = false;
		}

		//Takes Input from player
		if (SDLevent.type == SDL_KEYDOWN)
		{
			//Arrow keys input
			#pragma region ArrowKeys
//Arrow Key Up
			if (SDLevent.key.keysym.sym == SDLK_UP)
			{
				std::cout << "UP ARROW" << std::endl;
			}

			//Arrow Key Down
			if (SDLevent.key.keysym.sym == SDLK_DOWN)
			{
				std::cout << "DOWN ARROW" << std::endl;
			}

			//Arrow Key Left
			if (SDLevent.key.keysym.sym == SDLK_LEFT)
			{
				std::cout << "LEFT ARROW" << std::endl;
			}

			//Arrow Key Right
			if (SDLevent.key.keysym.sym == SDLK_RIGHT)
			{
				std::cout << "RIGHT ARROW" << std::endl;
			}
#pragma endregion

			//Space Key
			if (SDLevent.key.keysym.sym == SDLK_SPACE)
			{
				std::cout << "SPACE" << std::endl;
			}
		}
	}
}

//Add Draw Stuff here
void App::DrawPlayer(int screenX, int screenY, int scale)
{
	SDL_Point a = { 0, 40 }, b{ 10, 0 }, c{ 20, 40 }; //{x, y}

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(_renderer, a.x + screenX, a.y + screenY, b.x + screenX, b.y + screenY);
	SDL_RenderDrawLine(_renderer, a.x + screenX, a.y + screenY, c.x + screenX, c.y + screenY);
	SDL_RenderDrawLine(_renderer, b.x + screenX, b.y + screenY, c.x + screenX, c.y + screenY);
	SDL_RenderPresent(_renderer);						//Updates the rendering
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

void App::Render()
{
	SDL_RenderClear(_renderer);
	//TODO: Render stuff.
	SDL_RenderCopy(_renderer, _playerTexture, NULL, &destRect);
	DrawPlayer(800 / 2, 600 / 2, 1);
	
	SDL_RenderPresent(_renderer);
}

void App::Clean()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
}
