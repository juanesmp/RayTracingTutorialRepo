#include "pch.h"
#include "MovingSphere.h"
#include "AABB.h"
#include "SphereUtils.h"

Vec3 MovingSphere::GetCenterAtTime(float time) const
{
	float alpha = ((time - time0) / (time1 - time0));
	return center0 + alpha * (center1 - center0);
}

bool MovingSphere::DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const
{
	Vec3 oc = ray.origin - GetCenterAtTime(ray.time);
	float a = Dot(ray.direction, ray.direction);
	float b = Dot(oc, ray.direction);
	float c = Dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float length = (-b - sqrtf(discriminant)) / a;
		if (length < maxLength && length > minLength)
		{
			FillHitRecord(length, ray, hit);
			return true;
		}
		else
		{
			length = (-b + sqrtf(discriminant)) / a;
			if (length < maxLength && length > minLength)
			{
				FillHitRecord(length, ray, hit);
				return true;
			}
		}
	}

	return false;
}

void MovingSphere::FillHitRecord(float length, const Ray & ray, HitRecord & hit) const
{
	hit.length = length;
	hit.point = ray.GetPointAtLength(length);
	hit.normal = (hit.point - GetCenterAtTime(ray.time)) / radius;
	hit.pMaterial = pMaterial;
	GetSpehereTextureUV(hit.point, hit.textureU, hit.textureV);
}

bool MovingSphere::GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const
{
	AABB startBox = GetSphereBoundingBox(GetCenterAtTime(startTime), radius);
	AABB endBox = GetSphereBoundingBox(GetCenterAtTime(endTime), radius);

	box = CombineAABBs(startBox, endBox);
	
	return true;
}
