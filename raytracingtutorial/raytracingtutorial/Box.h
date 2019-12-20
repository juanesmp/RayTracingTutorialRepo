#pragma once
#include "Hitable.h"

class Box :	public Hitable
{
public:
	Box() {}
	Box(const Vec3 & _min, const Vec3 & _max, Material * pMaterial);

	virtual bool DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const override;
	virtual bool GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const override;

private:
	Vec3 min, max;
	Hitable* facesList;
};

