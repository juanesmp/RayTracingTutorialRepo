#pragma once

#include "Ray.h"

class Material;

struct HitRecord
{
	float length;
	Vec3 point;
	Vec3 normal;
	Material* pMaterial;
};

class Hitable
{
public:
	virtual bool DoesHit(const Ray& ray, float minLength, float maxLength, HitRecord& hit) const = 0;
};