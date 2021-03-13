#pragma once

#include "Game.h"

class InputManger : public Game
{
public:
	void GetInput(Entity& player, SDL_Event* poolEvent)
	{
		if (event.type == SDL_KEYDOWN)
		{
			//Moves player forward
			if (event.key.keysym.sym == SDLK_UP)
			{
				player.GetComponent<PhysicsComponent>().velocity += player.GetComponent<Transform>().GetForward() * 0.1f;
			}

			//Rotates player to the right
			if (event.key.keysym.sym == SDLK_RIGHT)
			{
				player.GetComponent<Transform>().angle += 10.0f;
				std::cout << player.GetComponent<Transform>().angle << std::endl;
			}

			//Rotates player to the left
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				player.GetComponent<Transform>().angle -= 10.0f;
				std::cout << player.GetComponent<Transform>().angle << std::endl;
			}

			//Makes player shoot
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				Entity* projectile = ProjectileFactory::GetNew("Resources/laserRed.png");
				projectile->GetComponent<Transform>().angle = player.GetComponent<Transform>().angle;
				projectile->GetComponent<Transform>().position = player.GetComponent<Transform>().position;
				projectile->GetComponent<PhysicsComponent>().velocity = projectile->GetComponent<Transform>().GetForward() * 3;
			}
		}
	};
};
