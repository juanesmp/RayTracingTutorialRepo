#pragma once
#include "Vec3.h"
#include "Ray.h"

class AABB
{
public:
	AABB() {};
	AABB(const Vec3 _min, const Vec3 _max) { min = _min; max = _max; }

	bool DoesRayHit(const Ray& ray, float minLength, float maxLength) const;

private:
	Vec3 min;
	Vec3 max;
};

