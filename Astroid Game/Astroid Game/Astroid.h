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
		Entity& astroid(entityManager.AddEntity());
		astroid.AddComponent<Transform>(250, 250);
		astroid.AddComponent<SpriteRenderer>("Resources/meteorGrey_tiny1.png");
		astroid.AddComponent<PhysicsComponent>();
		astroid.AddComponent<ScreenWrapign>();
		astroid.GetComponent<PhysicsComponent>().velocity = Eigen::Vector2f(1.0f, 5.0f);
	}
	/*
	void SpawnAstroidChildren(int childAmount, int astroidSize, Eigen::Vector2f parentPosition)
	{
		//Creates 2 children
		if (astroidSize > 1)
		{
			for (int i = 0; i < childAmount; i++)
			{
				Entity& astroidChild(entityManager.AddEntity());
				astroidChild.AddComponent<Transform>(parentPosition.x(), parentPosition.y());
				astroidChild.AddComponent<SpriteRenderer>("Resources/meteorGrey_tiny1.png");
				astroidChild.AddComponent<PhysicsComponent>();
				astroidChild.GetComponent<PhysicsComponent>().velocity = Eigen::Vector2f(rand() % 2, rand() % 2);
			}
		}
	}
	*/

private:
	Entity _object;
	int _astroidSize = 3;
	float _astroidSpeed = 1;
};
