#pragma once
#include "Components.h"
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

	Eigen::Vector2f GetForward()
	{
		const float angleInRad = DegreesToRadians(angle);
		return Eigen::Vector2f(cos(angleInRad), sin(angleInRad));
	}
};
