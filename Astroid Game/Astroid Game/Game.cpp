#include "Game.h"
#include "ECS.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Components.h"
#include "ScreenWraping.h"
#include "ProjectileFactory.h"
#include "Astroid.h"

#include <iostream>

Manager* Game::entityManager = new Manager();
Astroid* astroidProperties = nullptr;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Entity& playerEntity(Game::entityManager->AddEntity());

ScreenWrapign* _screenwrap = new ScreenWrapign();

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	#pragma region WindowPrep
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

	_screenwrap->SetScreenSize(width, height);
#pragma endregion

	for (int i = 0; i < 2; i++)
	{
		astroidProperties->SpawnAstroid(entityManager);
	}

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
				playerEntity.GetComponent<PhysicsComponent>().velocity += playerEntity.GetComponent<Transform>().GetForward() * 0.1f;
				break;
			}

			//Arrow Key Down
			case SDLK_DOWN:
			{
				std::cout << "DOWN ARROW" << std::endl;
				playerEntity.GetComponent<PhysicsComponent>().velocity -= playerEntity.GetComponent<Transform>().GetForward() * 0.1f;
				break;
			}

			//Arrow Key Left
			case SDLK_LEFT:
			{
				std::cout << "LEFT ARROW" << std::endl;
				if (playerEntity.GetComponent<Transform>().angle < 360 || playerEntity.GetComponent<Transform>().angle -360)
				{
					playerEntity.GetComponent<Transform>().angle -= 10.0f;
				}
				break;
			}

			//Arrow Key Right
			case SDLK_RIGHT:
			{
				std::cout << "RIGHT ARROW" << std::endl;
				if (playerEntity.GetComponent<Transform>().angle > 360 || playerEntity.GetComponent<Transform>().angle < 360)
				{
					playerEntity.GetComponent<Transform>().angle += 10.0f;
				}
				break;
			}

#pragma endregion

			//Space Key
			case SDLK_SPACE:
			{
				std::cout << "SPACE" << std::endl;
				Entity* projectile = ProjectileFactory::GetNew("Resources/laserRed.png");
				projectile->GetComponent<Transform>().angle = playerEntity.GetComponent<Transform>().angle;
				projectile->GetComponent<Transform>().position = playerEntity.GetComponent<Transform>().position;
				projectile->GetComponent<PhysicsComponent>().velocity = projectile->GetComponent<Transform>().GetForward() * 3;
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
	entityManager->Refresh();
	entityManager->Update();

	for (std::unique_ptr<Entity>& e : *entityManager->GetEntities())
	{
		_screenwrap->WrapWindow(&e.get()->GetComponent<Transform>());
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	entityManager->Draw();

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
