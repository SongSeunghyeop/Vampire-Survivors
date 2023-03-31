 #pragma once
#include <math.h>
#include <stdlib.h>
#pragma comment(lib, "msimg32.lib")

#define PI 3.141592f


class MyRGB
{
public:
	MyRGB(int r, int g, int b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	};
	int r, g, b;
};

struct Vector2 
{
	static Vector2 Up;
	static Vector2 Right;
	static Vector2 One;
	static Vector2 Zero;
	static Vector2 Radar_Size;

	float x, y;

	Vector2() : x(0.0f), y(0.0f) { }
	Vector2(float a, float b) : x(a), y(b) { }

	Vector2(const Vector2&) = default;
	Vector2& operator = (const Vector2&) = default;
	Vector2(Vector2&&) = default;
	Vector2& operator = (Vector2&&) = default;

	Vector2 operator+(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x + other.x;
		temp.y = y + other.y;

		return temp;
	}
	Vector2 operator-(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x - other.x;
		temp.y = y - other.y;

		return temp;
	}
	Vector2 operator*(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x * other.x;
		temp.y = y * other.y;

		return temp;
	}
	Vector2 operator*(const float ratio)
	{
		Vector2 temp;
		temp.x = x * ratio;
		temp.y = y * ratio;

		return temp;
	}
	Vector2 operator/(const float ratio)
	{
		if (ratio == 0.0f)
			return *this;
		Vector2 temp;
		temp.x = x / ratio;
		temp.y = y / ratio;

		return temp;
	}
	void operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
	}
	void operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}
	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2& Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;

		return *this;
	}
};

namespace my::math
{
	//float x = dir.x * cosf(PI / 5.0f) - dir.y * sinf(PI / 5.0f);
	//float y = dir.x * sinf(PI / 5.0f) + dir.y * cosf(PI / 5.0f);

	inline static Vector2 Rotate(Vector2 vector, int degree)
	{
		float radian = (degree / 180.0f) * PI;
		vector.Normalize();

		float x = vector.x * cosf(radian) - vector.y * sinf(radian);
		float y = vector.x * sinf(radian) + vector.y * cosf(radian);
		//atan
		//atan();
		return Vector2(x, y);
	}
	inline static float Dot(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}
	inline static float Cross(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}
}

