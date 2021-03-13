#pragma once

#include "Components.h"
#include "Eigen/Dense"
#include "SpriteRenderer.h"
#include "SDL.h"
#include "Game.h"
#include "ScreenWraping.h"

class Astroid : public Component
{
public:
	Astroid();
	~Astroid();

	void SpawnAstroid(Manager* entityManager)
	{
		Entity& astroid(Game::entityManager->AddEntity());
		astroid.AddComponent<Transform>(250, 250);
		astroid.AddComponent<SpriteRenderer>("Resources/meteorGrey_big2.png");
		astroid.AddComponent<PhysicsComponent>();
		astroid.AddComponent<ScreenWrapign>();
		astroid.GetComponent<PhysicsComponent>().velocity = Eigen::Vector2f(rand() % 2, rand() % 4);
		astroid.GetComponent<PhysicsComponent>().constRot = rand() % 3;

	}

	void OnDestroyAstroid(Eigen::Vector2f astroidPosition)
	{
		SpawnAstroidChildren(2, _astroidSize, astroidPosition);
	}

	void SpawnAstroidChildren(int childAmount, int astroidSize, Eigen::Vector2f parentPosition)
	{
		//Creates 2 children
		if (astroidSize > 1)
		{
			for (int i = 0; i < childAmount; i++)
			{
				Entity& astroidChild(Game::entityManager->AddEntity());
				astroidChild.AddComponent<Transform>(parentPosition.x(), parentPosition.y());
				
				switch (astroidSize)
				{

				case 3:
				{
					astroidChild.AddComponent<SpriteRenderer>("Resources/meteorGrey_med2.png");
					break;
				}

				case 2:
				{
					astroidChild.AddComponent<SpriteRenderer>("Resources/meteorGrey_tiny1.png");
					break;
				}

				default:
					break;
				}
				
				astroidChild.AddComponent<PhysicsComponent>();
				astroidChild.GetComponent<PhysicsComponent>().velocity = Eigen::Vector2f(rand() % 2, rand() % 2);
			}
			astroidSize--;
		}
	}

private:
	int _astroidSize = 3;
	float _astroidSpeed = 1;
};
