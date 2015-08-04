#pragma once

#include "Vector2.h"

struct Circle
{
	Vector2 centre;
	float radius;

	Circle()
	{
		centre.x = 0.0f;
		centre.y = 0.0f;
		radius = 0.0f;
	}

	Circle(float x, float y, float radius)
	{
		centre.x = x;
		centre.y = y;
		this->radius = radius;
	}

	Circle(Vector2 centre, float radius)
	{
		this->centre = centre;
		this->radius = radius;
	}
};