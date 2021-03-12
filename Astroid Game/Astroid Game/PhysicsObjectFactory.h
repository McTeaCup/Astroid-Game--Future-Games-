#pragma once

class Entity;

class PhysicsObjectFactory
{
public:
	static Entity* GetNew(const char* spritePath);
};