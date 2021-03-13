#pragma once

#include "Components.h"
#include "Eigen/Dense"

class PhysicsComponent : public Component
{
private:
	Transform* _transform;
public:
	Eigen::Vector2f velocity;
	float constRot;

	void Init() override
	{
		_transform = &entity->GetComponent<Transform>();
		
		velocity.x() = 0;
		velocity.y() = 0;
	}

	void Update() override
	{
		_transform->position += velocity;
		_transform->angle += constRot;
	}
};