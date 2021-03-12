#include "PhysicsObjectFactory.h"
#include "Components.h"
#include "Game.h"

Entity* PhysicsObjectFactory::GetNew(const char* spritePath)
{
	Entity* newEntity = &Game::entityManager->AddEntity();

	newEntity->AddComponent<Transform>(300,300);
	newEntity->AddComponent<SpriteRenderer>(spritePath, 90);
	newEntity->AddComponent<PhysicsComponent>();

	return newEntity;
}
