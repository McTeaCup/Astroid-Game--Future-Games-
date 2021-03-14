#include "Game.h"
#include "ECS.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Components.h"
#include "ScreenWraping.h"
#include "ProjectileFactory.h"
#include "Astroid.h"
#include "InputManager.h"

#include <iostream>

Manager* Game::entityManager = new Manager();
Astroid* astroidProperties = nullptr;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
InputManger* input;
Entity& playerEntity(Game::entityManager->AddEntity());
ScreenWrapign* _screenwrap = new ScreenWrapign();

Game::Game(){}

Game::~Game(){}

//Creates window
void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	#pragma region Window Instansiation
	//Saves the screen size
	_screenwrap->SetScreenSize(width, height);

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
#pragma endregion

	#pragma region Creates Window
	SDL_Window* window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (window == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		_isRunning = false;
		return;
	}
	std::cout << "Window created." << std::endl;
#pragma endregion

	#pragma region CreatesRenderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		_isRunning = false;
		return;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	std::cout << "Renderer created." << std::endl;
#pragma endregion

#pragma endregion

	#pragma region Spawns Player & Astoid
	//Spawn 2 Astroids
	for (int i = 0; i < 2; i++)
	{
		astroidProperties->SpawnAstroid(entityManager);
	}

	//Creates player in the middle of the screen
	playerEntity.AddComponent <Transform>(width / 2, height / 2);
	playerEntity.AddComponent<SpriteRenderer>("Resources/playerShip.png", 90);
	playerEntity.AddComponent<PhysicsComponent>();
	_isRunning = true;
#pragma endregion
}

//Take care of events (duh)
void Game::HandleEvents()
{
	while (SDL_PollEvent(&event))
	{
		//Closes game when window closes
		if (event.type == SDL_QUIT)
		{
			_isRunning = false;
		}
		
		//Applies input to player
		input->GetInput(playerEntity, &event, tickRate);
	}
}

//Called allways
void Game::Update()
{
	entityManager->Refresh();
	entityManager->Update();

	tickRate+= 0.015f;
	if (input->event.key.keysym.sym == SDLK_SPACE && tickRate > 0.5f)
	{
		tickRate = 0;
	}
	
	//Updates the screenwrapping for each entity
	for (std::unique_ptr<Entity>& e : *entityManager->GetEntities())
	{
		_screenwrap->WrapWindow(&e.get()->GetComponent<Transform>());
	}
}

//Updates the window's renderer
void Game::Render()
{
	SDL_RenderClear(renderer);

	entityManager->Draw();

	SDL_RenderPresent(renderer);
}

//Called when closing the window
void Game::Clean()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::RestartGame()
{
	for (std::unique_ptr<Entity>& e : *entityManager->GetEntities())
	{
		_screenwrap->WrapWindow(&e.get()->GetComponent<Transform>());
	}

	//Spawn 2 Astroids
	for (int i = 0; i < 2; i++)
	{
		astroidProperties->SpawnAstroid(entityManager);
	}

	//Creates player in the middle of the screen
	playerEntity.AddComponent <Transform>(_screenwrap->_screenWidhth / 2, _screenwrap->_screenHight / 2);
	playerEntity.AddComponent<SpriteRenderer>("Resources/playerShip.png", 90);
	playerEntity.AddComponent<PhysicsComponent>();
	_isRunning = true;
}
