#pragma once
#include "Hitable.h"

class FlipNormals : public Hitable
{
public:
	FlipNormals() {}
	FlipNormals(Hitable *child) : pChild(child) {}

	virtual bool DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const override;
	virtual bool GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const override;

private:
	Hitable* pChild;
};

