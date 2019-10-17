#include "pch.h"
#include "Vec3.h"
#include <math.h>

Vec3::Vec3()
{
}

Vec3::Vec3(float e0, float e1, float e2)
{
	e[0] = e0;
	e[1] = e1;
	e[2] = e2;
}

Vec3 Reflect(const Vec3 & v, const Vec3 & normal)
{
	return v - 2.0f * Dot(v, normal) * normal;
}

bool Refract(const Vec3 & v, const Vec3 & normal, float niOverNt, Vec3 & refracted)
{
	Vec3 unitV = ConvertToUnitVector(v);
	float dt = Dot(unitV, normal);
	float discriminant = 1.0f - niOverNt * niOverNt * (1 - dt * dt);
	if (discriminant > 0)
	{
		refracted = niOverNt * (unitV - normal * dt) - normal * sqrtf(discriminant);
		return true;
	}
	else
	{
		return false;
	}
}



