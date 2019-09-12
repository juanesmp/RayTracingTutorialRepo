#pragma once

#include "Vec3.h"

class Ray
{
public:
	Ray();
	Ray(const Vec3& _origin, const Vec3& _direction);

	Vec3 origin;
	Vec3 direction;
};

