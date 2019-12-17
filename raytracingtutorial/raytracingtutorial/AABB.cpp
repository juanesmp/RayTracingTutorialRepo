#include "pch.h"
#include "AABB.h"
#include "floatutils.h"

bool AABB::DoesRayHit(const Ray & ray, float minLength, float maxLength) const
{
	for (int i = 0; i < 3; i++)
	{
		float invDirection = 1.0f / ray.direction.e[i];
		float t0 = (min.e[i] - ray.origin.e[i]) * invDirection;
		float t1 = (max.e[i] - ray.origin.e[i]) * invDirection;
		
		if (invDirection < 0.0f)
		{
			float temp = t0;
			t0 = t1;
			t1 = temp;
		}

		minLength = GetMaxFloat(t0, minLength);
		maxLength = GetMinFloat(t1, maxLength);
	
		if (maxLength <= minLength)
			return false;
	}
	
	return true;
}
