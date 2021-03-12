#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Components.h"
#include "ScreenWraping.h"

#include <iostream>

Manager entityManager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Entity& playerEntity(entityManager.AddEntity());

GameObject* _player;
GameObject* _astroid;
ScreenWrapign* _screenwrap = new ScreenWrapign();

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


	_astroid = new GameObject();
	_astroid->OnSpawn(100, 100, true);

	_screenwrap->SetScreenSize(width, height);

	_player = new GameObject();

	playerEntity.AddComponent <Transform>(100, 100);
	playerEntity.AddComponent<SpriteRenderer>("Resources/playerShip.png", 90);
	playerEntity.AddComponent<PhysicsComponent>();
	_isRunning = true;
}

void Game::HandleEvents()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			_isRunning = false;
		}

		//Takes Input from player
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
#pragma region ArrowKeys

				//Arrow Key Up
			case SDLK_UP:
			{
				std::cout << "UP ARROW" << std::endl;
				_player->_yvelocity -= 0.1f;
				playerEntity.GetComponent<PhysicsComponent>().velocity += playerEntity.GetComponent<Transform>().GetForward() * 0.1f;
				break;
			}

			//Arrow Key Down
			case SDLK_DOWN:
			{
				std::cout << "DOWN ARROW" << std::endl;
				_player->_yvelocity += 0.1f;
				playerEntity.GetComponent<PhysicsComponent>().velocity -= playerEntity.GetComponent<Transform>().GetForward() * 0.1f;
				break;
			}

			//Arrow Key Left
			case SDLK_LEFT:
			{
				std::cout << "LEFT ARROW" << std::endl;
				if (_player->angle < 360 || _player->angle > -360)
				{
					_player->angle -= 1.0f;
					playerEntity.GetComponent<Transform>().angle -= 10.0f;
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
					playerEntity.GetComponent<Transform>().angle += 10.0f;
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
	entityManager.Refresh();
	entityManager.Update();

	_screenwrap->WrapWindow(playerEntity);
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	entityManager.Draw();
	_player->Render();
	_astroid->Render();

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
