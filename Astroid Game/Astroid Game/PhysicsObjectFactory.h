#pragma once
#include "ECS.h"
#include "Game.h"

class PhysicsObjectFactory
{
	static Entity* GetNew(const char* spritePath);
};