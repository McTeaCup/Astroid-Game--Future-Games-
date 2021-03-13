#pragma once
#include "ECS.h"
#include "Eigen/Dense"
#include "MathHelpers.h"

class Transform : public Component
{
public:
	Eigen::Vector2f position;
	Eigen::Vector2f scale;
	float angle;


	Transform()
	{
		position = Eigen::Vector2f(0, 0);
		scale = Eigen::Vector2f(1, 1);
		angle = 0;
	}

	Transform(int x, int y)
	{
		position = Eigen::Vector2f(x, y);
		scale = Eigen::Vector2f(1, 1);
		angle = 0;
	}

	Transform(float x, float y, float a)
	{
		position = Eigen::Vector2f(x, y);
		scale = Eigen::Vector2f(1, 1);
		angle = a;
	}

	Eigen::Vector2f GetForward()
	{
		const float angleInRad = DegreesToRadians(angle);
		return Eigen::Vector2f(cos(angleInRad), sin(angleInRad));
	}
};
