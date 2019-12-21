#include "pch.h"
#include "Translate.h"
#include "AABB.h"

bool Translate::DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const
{
	Ray movedRay(ray.origin - offset, ray.direction, ray.time);
	
	if (pChild->DoesRayHit(movedRay, minLength, maxLength, hit))
	{
		hit.point += offset;
		return true;
	}

	return false;
}

bool Translate::GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const
{
	if (pChild->GetBoundingBoxAtTime(startTime, endTime, box))
	{
		box = AABB(box.GetMin() + offset, box.GetMax() + offset);
		return true;
	}
	return false;
}
