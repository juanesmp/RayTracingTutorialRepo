#pragma once

#include "Hitable.h"

class HitableList :	public Hitable
{
public:
	HitableList() {}
	
	HitableList(Hitable **l, int lSize) 
	{ 
		list = l; 
		listSize = lSize; 
	}

	virtual bool DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const override;
	virtual bool GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const override;

	Hitable **list;
	int listSize;
};

