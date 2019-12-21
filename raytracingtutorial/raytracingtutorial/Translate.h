#pragma once
#include "Hitable.h"

class Translate : public Hitable
{
public:
	Translate(Hitable * child, const Vec3 & _offset) : pChild(child), offset(_offset) {}

	virtual bool DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const override;
	virtual bool GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const override;

private:
	Hitable* pChild;
	Vec3 offset;
};

