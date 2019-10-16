#pragma once

#include "Ray.h"

struct HitRecord
{
	float lenght;
	Vec3 point;
	Vec3 normal;
};

class Hitable
{
public:
	virtual bool DoesHit(const Ray& ray, float minLenght, float maxLenght, HitRecord& hit) const = 0;
};