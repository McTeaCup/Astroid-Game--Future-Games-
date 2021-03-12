#pragma once
#include "ECS.h"
#include "Game.h"

class PhysicsObjectFactory
{
public:
	static Entity* GetNew(const char* spritePath);
};