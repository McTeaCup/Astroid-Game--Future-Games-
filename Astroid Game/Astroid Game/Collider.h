#pragma once
#include "ECS.h"
#include "Transform.h"

class Collider : public Component
{
private:
	Transform* _transform;

public:
	float size;

	Collider(float size)
	{
		this->size = size;
	}

	Eigen::Vector2f GetPosition()
	{
		return _transform->position;
	}
	
	void Init() override
	{
		_transform = &entity->GetComponent<Transform>();
	}
};
