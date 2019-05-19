#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f

struct Vector2
{
	float x;
	float y;

	Vector2(float _x = 0.0f, float _y = 0.0f)
		: x(_x), y(_y) {}

	float MagnitudeSqr()
	{
		return x*x + y*y;
	}

	float Magnitude()
	{
		return (float)sqrt(x*x + y*y);
	}

	bool Between(Vector2& topleft, Vector2& bottomright)
	{
		if (x >= topleft.x && x <= bottomright.x)
			if (y >= topleft.y &&  y <= bottomright.y)
				return true;

		return false;
	}

	bool Between(Vector2& topleft, float w, float h)
	{
		if (x >= topleft.x && x <= topleft.x + w)
			if (y >= topleft.y &&  y <= topleft.y + h)
				return true;

		return false;
	}

	Vector2 Normalize()
	{
		float mag = Magnitude();

		return Vector2(x / mag, y / mag);
	}

	Vector2& operator +=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2& operator -=(const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	bool operator ==(const Vector2& rhs)
	{
		return (x == rhs.x && y == rhs.y);
	}
};

inline Vector2 operator +(const Vector2& lhs, const Vector2 rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2 operator -(const Vector2& lhs, const Vector2 rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector2 operator *(const Vector2& lhs, const float& rhs)
{
	return Vector2(lhs.x * rhs, lhs.y * rhs);
}
inline Vector2 RotateVector(Vector2& vec, float angle)
{
	float radAngle = (float)(angle * DEG_TO_RAD);

	return Vector2(((float)vec.x * cos(radAngle) - vec.y * sin(radAngle)), ((float)(vec.x * sin(radAngle) + vec.y * cos(radAngle))));
}

inline Vector2 Lerp(Vector2& start, Vector2& end, float time)
{
	if (time <= 0.0f)
		return start;
	else if (time >= 1.0f)
		return end;
	else
	{
		Vector2 dir = (end - start).Normalize();
		float mag = (end - start).Magnitude();

		return start + dir * mag * time;
	}
}

const Vector2 VEC2_ZERO = { 0.0f, 0.0f };
const Vector2 VEC2_ONE = { 1.0f, 1.0f };
const Vector2 VEC2_UP = { 0.0f, 1.0f };
const Vector2 VEC2_RIGHT = { 1.0f, 0.0f };

#endif