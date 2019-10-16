#include "pch.h"
#include "HitableList.h"

bool HitableList::DoesHit(const Ray & ray, float minLenght, float maxLenght, HitRecord & hit) const
{
	HitRecord tempHit;
	bool doesHit = false;
	float closestLenght = maxLenght;
	for (int i = 0; i < listSize; i++)
	{
		if (list[i]->DoesHit(ray, minLenght, closestLenght, tempHit))
		{
			doesHit = true;
			closestLenght = tempHit.lenght;
			hit = tempHit;
		}
	}

	return doesHit;
}
