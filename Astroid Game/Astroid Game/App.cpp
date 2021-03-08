#include "App.h"

#include <iostream>

App::App()
{
}

App::~App()
{
}

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

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		_isRunning = false;
		return;
	}
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	std::cout << "Renderer created." << std::endl;

	_isRunning = true;
}

void App::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		_isRunning = false;
		break;
	default:
		break;
	}
}

void App::Render()
{
	SDL_RenderClear(_renderer);
	//TODO: Render stuff.
	SDL_RenderPresent(_renderer);
}

void App::Clean()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
}
