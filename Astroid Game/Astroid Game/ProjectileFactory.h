#pragma once

class Entity;

class ProjectileFactory
{
public:
	static Entity* GetNew(const char* spritePath);
};