#include "pch.h"
#include "Sphere.h"
#include "AABB.h"
#include "SphereUtils.h"

#define _USE_MATH_DEFINES
#include <math.h>

bool Sphere::DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const
{
	Vec3 oc = ray.origin - center;
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

void Sphere::FillHitRecord(float length, const Ray & ray, HitRecord & hit) const
{
	hit.length = length;
	hit.point = ray.GetPointAtLength(length);
	hit.normal = (hit.point - center) / radius;
	hit.pMaterial = pMaterial;
	GetSpehereTextureUV(hit.point, hit.textureU, hit.textureV);
}

bool Sphere::GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const
{
	box = GetSphereBoundingBox(center, radius);
	return true;
}
