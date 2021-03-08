#include <iostream>
#include "SDL.h"

class Game
{
public:
	void Input();

private:
	SDL_Event SDLevent;
};

//Input from the player
void Game::Input()
{
	while (SDL_PollEvent(&SDLevent))
	{
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