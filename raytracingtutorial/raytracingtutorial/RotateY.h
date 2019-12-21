#pragma once
#include "Hitable.h"
#include "AABB.h"

class RotateY :	public Hitable
{
public:
	RotateY(Hitable* child, float angle);

	virtual bool DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const override;
	virtual bool GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const override;

private:
	Hitable * pChild;
	
	float sinTheta;
	float cosTheta;

	bool hasBox;
	AABB aabb;
};

