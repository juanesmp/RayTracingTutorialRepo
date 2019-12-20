#include "pch.h"
#include "FlipNormals.h"

bool FlipNormals::DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const
{
	if (pChild->DoesRayHit(ray, minLength, maxLength, hit))
	{
		hit.normal = -hit.normal;
		return true;
	}
	return false;
}

bool FlipNormals::GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const
{
	return pChild->GetBoundingBoxAtTime(startTime, endTime, box);
}
