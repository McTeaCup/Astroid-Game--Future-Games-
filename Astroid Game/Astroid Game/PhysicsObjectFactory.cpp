#include "PhysicsObjectFactory.h"
#include "Components.h"

Entity* PhysicsObjectFactory::GetNew(const char* spritePath)
{
	Entity* newEntity = &Game::entityManager->AddEntity();

	newEntity->AddComponent<Transform>();
	newEntity->AddComponent<SpriteRenderer>(spritePath, 90);
	newEntity->AddComponent<PhysicsComponent>();

	return newEntity;
}
