#include "pch.h"
#include "HitableList.h"
#include "AABB.h"

bool HitableList::DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const
{
	HitRecord tempHit;
	bool doesHit = false;
	float closestLength = maxLength;
	for (int i = 0; i < listSize; i++)
	{
		if (list[i]->DoesRayHit(ray, minLength, closestLength, tempHit))
		{
			doesHit = true;
			closestLength = tempHit.length;
			hit = tempHit;
		}
	}

	return doesHit;
}

bool HitableList::GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const
{
	if (listSize <= 0) 
		return false;

	if (!list[0]->GetBoundingBoxAtTime(startTime, endTime, box))
		return false;

	AABB tempBox;
	for (int i = 1; i < listSize; i++)
	{
		if (list[i]->GetBoundingBoxAtTime(startTime, endTime, tempBox))
			box = CombineAABBs(box, tempBox);
		else
			return false;
	}

	return true;
}
