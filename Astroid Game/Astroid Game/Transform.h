#pragma once
#include "Components.h"
#include "Eigen/Dense"

class Transform : public Component
{
public:
	Eigen::Vector2f position;
	
	Transform()
	{
		position.x() = 0;
		position.y() = 0;
	}
	Transform(int x, int y)
	{
		position.x() = x;
		position.y() = y;
	}
	
	void Update() override
	{
	}
};