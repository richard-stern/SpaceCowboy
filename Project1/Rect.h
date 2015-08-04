#pragma once

#include "Vector2.h"

struct Rect
{
	Vector2 min;
	Vector2 max;

	Rect()
	{
		min.x = 0.0f;
		min.y = 0.0f;
		max.x = 0.0f;
		max.y = 0.0f;
	}

	Rect(float minX, float minY, float maxX, float maxY)
	{
		min.x = minX;
		min.y = minY;
		max.x = maxX;
		max.y = maxY;
	}

	Rect(Vector2 min, Vector2 max)
	{
		this->min = min;
		this->max = max;
	}
};