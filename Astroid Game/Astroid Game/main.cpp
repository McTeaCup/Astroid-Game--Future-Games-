#include <iostream>
#include "SDL.h"
#include "Game.h"

Game* game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game();

	game->Init("SDL App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1120, false);

	const int desiredFPS = 60;
	const int desiredFrameTime = 1000 / desiredFPS;

	const int fixedDeltaTime = static_cast<int>(0.01f * 1000);

	Uint32 frameStartTime = SDL_GetTicks();
	int accumulator = 0;

	while (game->Running())
	{
		const Uint32 newTime = SDL_GetTicks();
		const int deltaTime = newTime - frameStartTime;
		frameStartTime = newTime;

		accumulator += deltaTime;

		while (accumulator >= fixedDeltaTime)
		{
			//Things that should run on a fixed step go here.
			accumulator -= fixedDeltaTime;
		}

		game->Update();
		game->HandleEvents();
		game->Render();

		const int frameTime = SDL_GetTicks() - frameStartTime;
		if (frameTime < desiredFrameTime)
			SDL_Delay(desiredFrameTime - frameTime);
	}

	game->Clean();

	return 0;
}



