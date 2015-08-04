#pragma once

#include <math.h>

struct Vector2
{
	float x;
	float y;

	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float Length() const
	{
		return sqrtf(LengthSqr());
	}

	float LengthSqr() const
	{
		return (x * x + y * y);
	}

	float Normalise()
	{
		float fLength = Length();
		if(fLength != 0.0f)
		{
			x = x / fLength;
			y = y / fLength;
		}
		return fLength;
	}

	void Clamp(float maxLength)
	{
		float fLength = Length();
		if(fLength != 0.0f && fLength > maxLength)
		{
			x /= fLength;
			y /= fLength;
			x *= maxLength;
			y *= maxLength;
		}
	}

	float Dot(const Vector2 rihs) const
	{
		return (x * rihs.x) + (y * rihs.y);
	}

	Vector2 Clamp(const Vector2& min, const Vector2& max) const
	{
		Vector2 result;
		result.x = x < min.x ? min.x : x;
		result.x = result.x > max.x ? max.x : result.x;
		result.y = y < min.y ? min.y : y;
		result.y = result.y > max.y ? max.y : result.y;

		return result;
	}

	Vector2 operator + (const Vector2 rhs) const
	{
		Vector2 result;
		result.x = x + rhs.x;
		result.y = y + rhs.y;

		return result;
	}

	Vector2& operator += (const Vector2 rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	Vector2 operator - (const Vector2 rhs) const
	{
		Vector2 result;
		result.x = x - rhs.x;
		result.y = y - rhs.y;

		return result;
	}

	Vector2& operator -= (const Vector2 rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}

	Vector2 operator * (const float rhs) const
	{
		Vector2 result;
		result.x = x * rhs;
		result.y = y * rhs;

		return result;
	}

	Vector2& operator *= (const float rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}

	Vector2 operator / (const float rhs) const
	{
		Vector2 result;
		result.x = x / rhs;
		result.y = y / rhs;

		return result;
	}

	Vector2& operator /= (const float rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		return *this;
	}
};