#pragma once

#include "Ray.h"

class Material;
class AABB;

struct HitRecord
{
	float length;
	Vec3 point;
	Vec3 normal;
	Material* pMaterial;
	float textureU;
	float textureV;
};

class Hitable
{
public:
	virtual bool DoesRayHit(const Ray& ray, float minLength, float maxLength, HitRecord& hit) const = 0;
	virtual bool GetBoundingBoxAtTime(float startTime, float endTime, AABB& box) const = 0;
};