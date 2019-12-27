#include "pch.h"
#include "ConstantMedium.h"
#include "Random.h"

bool ConstantMedium::DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const
{
	HitRecord hit1, hit2;

	if (pBoundary->DoesRayHit(ray, -1000000, 1000000, hit1))
	{
		if (pBoundary->DoesRayHit(ray, hit1.length + 0.0001f, 1000000, hit2))
		{
			if (hit1.length < minLength)
				hit1.length = minLength;
			if (hit2.length > maxLength)
				hit2.length = maxLength;
			if (hit1.length >= hit2.length)
				return false;
			if (hit1.length < 0)
				hit1.length = 0;

			float distanceInsideBoundary = (hit2.length - hit1.length) * ray.direction.GetLength();
			float hitDistance = -(1/density) * logf(GetRandom0To1());

			if (hitDistance < distanceInsideBoundary)
			{
				hit.length = hit1.length + hitDistance / ray.direction.GetLength();
				hit.point = ray.GetPointAtLength(hit.length);
				hit.normal = Vec3(1, 0, 0);
				hit.pMaterial = pMaterial;
				return true;
			}
		}
	}
	
	return false;
}

bool ConstantMedium::GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const
{
	return pBoundary->GetBoundingBoxAtTime(startTime, endTime, box);
}
