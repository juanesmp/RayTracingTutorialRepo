#include "pch.h"
#include "HitableList.h"

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
