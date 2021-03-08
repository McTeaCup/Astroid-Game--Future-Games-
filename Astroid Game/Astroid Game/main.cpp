#include <iostream>
#include "SDL.h"
#include "App.h"
#include "Game.h"

App* app = nullptr;
Game* game = new Game;

int main(int argc, char *argv[])
{
	app = new App();

	app->Init("SDL App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	const int desiredFPS = 60;
	const int desiredFrameTime = 1000 / desiredFPS;

	const int fixedDeltaTime = static_cast<int>(0.01f * 1000);

	Uint32 frameStartTime = SDL_GetTicks();
	int accumulator = 0;

	while (app->Running())
	{
		const Uint32 newTime = SDL_GetTicks();
		const int deltaTime = newTime - frameStartTime;
		frameStartTime = newTime;

		//Checks if the game class exists
		if (game != NULL)
		{
			game->Input();
		}

		accumulator += deltaTime;

		//std::cout << deltaTime << std::endl;

		while (accumulator >= fixedDeltaTime)
		{
			//Things that should run on a fixed step go here.
			//std::cout << fixedDeltaTime << std::endl;
			accumulator -= fixedDeltaTime;
		}

		app->HandleEvents();
		app->Render();

		const int frameTime = SDL_GetTicks() - frameStartTime;
		if (frameTime < desiredFrameTime)
			SDL_Delay(desiredFrameTime - frameTime);
	}

	app->Clean();

	return 0;
}
