#pragma once
#include "Components.h"
#include "Eigen/Dense"

class Transform : public Component
{
public:
	Eigen::Vector2f position;
	float angle;
	
	
	Transform()
	{
		position.x() = 0;
		position.y() = 0;
		angle = 0;
	}
	Transform(int x, int y)
	{
		position.x() = x;
		position.y() = y;
		angle = 0;
	}
	Transform(float x, float y, float a)
	{
		position.x() = x;
		position.y() = y;
		angle = a;
	}
	
	void Update() override
	{
	}
};