#pragma once

#include "Vec3.h"

class Ray
{
public:
	Ray();
	Ray(const Vec3& _origin, const Vec3& _direction);

	Vec3 GetPointAtLenght(float lenght) const { return origin + lenght * direction; }

	Vec3 origin;
	Vec3 direction;
};

