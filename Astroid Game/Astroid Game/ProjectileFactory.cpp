#include "ProjectileFactory.h"
#include "Components.h"
#include "Game.h"

Entity* ProjectileFactory::GetNew(const char* spritePath)
{
	Entity* newEntity = &Game::entityManager->AddEntity();

	newEntity->AddComponent<Transform>(-100,-100);
	newEntity->AddComponent<SpriteRenderer>(spritePath, 90);
	newEntity->AddComponent<PhysicsComponent>();

	return newEntity;
}
