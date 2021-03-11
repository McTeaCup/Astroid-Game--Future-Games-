#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"

#include <iostream>

GameObject* _player;

SDL_Renderer* Game::renderer = nullptr;
 
Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
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

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		_isRunning = false;
		return;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	std::cout << "Renderer created." << std::endl;

	_isRunning = true;

	_player = new GameObject("Resources/playerShip.png");
}

void Game::HandleEvents()
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
			switch (SDLevent.key.keysym.sym)
			{
			#pragma region ArrowKeys
			
			//Arrow Key Up
			case SDLK_UP:
			{
				std::cout << "UP ARROW" << std::endl;
				_player->_yvelocity -= 0.1f;
				std::cout << _player->_yvelocity << std::endl;
				break;
			}

			//Arrow Key Down
			case SDLK_DOWN:
			{
				std::cout << "DOWN ARROW" << std::endl;
				_player->_yvelocity += 0.1f;
				std::cout << _player->_yvelocity << std::endl;
				break;
			}

			//Arrow Key Left
			case SDLK_LEFT:
			{
				std::cout << "LEFT ARROW" << std::endl;
				if (_player->angle < 360 || _player->angle > -360)
				{
					_player->angle -= 1.0f;
				}
				else
				{
					_player->angle = 0;
				}
				std::cout << _player->angle << std::endl;
				break;
			}

			//Arrow Key Right
			case SDLK_RIGHT:
			{
				std::cout << "RIGHT ARROW" << std::endl;
				if (_player->angle > 360 || _player->angle < 360)
				{
					_player->angle += 1.0f;
				}
				else
				{
					_player->angle = 0;
				}
				std::cout << _player->angle << std::endl;
				break;
			}

#pragma endregion

			//Space Key
			case SDLK_SPACE:
			{
				std::cout << "SPACE" << std::endl;
				break;
			}
			
			default:
				break;
			}
		}
	}
}

void Game::Update()
{
	_player->Update();
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	_player->Render();
	
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
