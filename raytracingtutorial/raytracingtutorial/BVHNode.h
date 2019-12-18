#pragma once
#include "Hitable.h"
#include "AABB.h"

class BVHNode : public Hitable
{
public:
	BVHNode() {};
	BVHNode(Hitable ** hitableList, int hitableCount, float startTime, float endTime);

	virtual bool DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const override;
	virtual bool GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const override;

private:
	Hitable *left;
	Hitable *right;
	AABB aabb;
};

