#include <iostream>
#include "SDL.h"
#include "App.h"

App* app = nullptr;

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
		app->DrawPlayer(800/2, 600 / 2, 1);
		const Uint32 newTime = SDL_GetTicks();
		const int deltaTime = newTime - frameStartTime;
		frameStartTime = newTime;

		accumulator += deltaTime;

		//std::cout << deltaTime << std::endl;

		while (accumulator >= fixedDeltaTime)
		{
			//Things that should run on a fixed step go here.
			//std::cout << fixedDeltaTime << std::endl;
			accumulator -= fixedDeltaTime;
		}

		app->HandleEvents();
		//app->Render();

		const int frameTime = SDL_GetTicks() - frameStartTime;
		if (frameTime < desiredFrameTime)
			SDL_Delay(desiredFrameTime - frameTime);
	}

	app->Clean();

	return 0;
}



