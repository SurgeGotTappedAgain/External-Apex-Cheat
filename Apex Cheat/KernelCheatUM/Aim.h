#pragma once
#include <vector>
#include <Windows.h>
#define M_PI 3.14159265

struct vec3
{
	float x, y, z;

	vec3 operator-(vec3 ape)
	{
		return { x - ape.x, y - ape.y, z - ape.z };
	}

	vec3 operator+(vec3 ape)
	{
		return { x + ape.x, y + ape.y, z + ape.z };
	}

	vec3 operator*(float ape)
	{
		return { x * ape, y * ape, z * ape };
	}

	vec3 operator/(float ape)
	{
		return { x / ape, y / ape, z / ape };
	}

	vec3 operator/=(float ape)
	{
		x /= ape;
		y /= ape;
		z /= ape;

		return *this;
	}

	vec3 operator+=(vec3 ape)
	{
		return { x += ape.x, y += ape.y, z += ape.z };
	}

	vec3 operator-=(vec3 ape)
	{
		return { x -= ape.x, y -= ape.y, z -= ape.z };
	}

	void Normalize()
	{
		while (x > 89.0f)
			x -= 180.f;

		while (x < -89.0f)
			x += 180.f;

		while (y > 180.f)
			y -= 360.f;

		while (y < -180.f)
			y += 360.f;
	}

	float Length()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	float Length2D()
	{
		return sqrt((x * x) + (y * y));
	}

	float DistTo(vec3 ape)
	{
		return (*this - ape).Length();
	}

	float Dist2D(vec3 ape)
	{
		return (*this - ape).Length2D();
	}
};

struct vec2
{
	float x, y;
};

struct bone_t
{
	BYTE pad[0xCC];
	float x;
	BYTE pad2[0xC];
	float y;
	BYTE pad3[0xC];
	float z;
};