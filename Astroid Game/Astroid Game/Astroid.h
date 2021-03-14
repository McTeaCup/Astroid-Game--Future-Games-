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

	/// <summary>
	/// Spawns Astroid with constant speed and roation
	/// </summary>
	/// <param name="entityManager"></param>
	void SpawnAstroid(Manager* entityManager)
	{
		Entity& astroid(Game::entityManager->AddEntity());
		astroid.AddComponent<Transform>(250, 250);
		astroid.AddComponent<SpriteRenderer>("Resources/meteorGrey_big2.png");
		astroid.AddComponent<PhysicsComponent>();
		astroid.AddComponent<Collider>(30);
		astroid.AddComponent<ScreenWrapign>();
		astroid.GetComponent<PhysicsComponent>().velocity = Eigen::Vector2f(rand() % 2, rand() % 4);
		astroid.GetComponent<PhysicsComponent>().constRot = rand() % 3;

		astroid.AddGroup(Game::Asteroids);
	}

	/// <summary>
	/// Creates smaler astroids
	/// </summary>
	/// <param name="astroidPosition"></param>
	void SpawnAstroidChildren(int childAmount, Eigen::Vector2f parentPosition)
	{

		for (int i = 0; i < childAmount; i++)
		{
			Entity& astroidChild(Game::entityManager->AddEntity());
			astroidChild.AddComponent<Transform>(parentPosition.x(), parentPosition.y());
			astroidChild.AddComponent<Collider>(20);
			astroidChild.AddComponent<SpriteRenderer>("Resources/meteorGrey_med2.png");
			astroidChild.AddComponent<PhysicsComponent>();
			astroidChild.AddComponent<ScreenWrapign>();
			astroidChild.GetComponent<PhysicsComponent>().velocity = Eigen::Vector2f(rand() % 2, rand() % 4);
			astroidChild.GetComponent<PhysicsComponent>().constRot = 3;
			astroidChild.AddGroup(Game::Asteroids);
		}
	}
};
