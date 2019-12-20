#include "pch.h"
#include "YZRectangle.h"
#include "AABB.h"

bool YZRectangle::DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const
{
	float length = (x - ray.origin.X()) / ray.direction.X();
	if (length < minLength || length > maxLength)
		return false;

	float y = ray.origin.Y() + length * ray.direction.Y();
	if (y < y0 || y > y1)
		return false;

	float z = ray.origin.Z() + length * ray.direction.Z();
	if (z < z0 || z > z1)
		return false;

	hit.textureU = (y - y0) / (y1 - y0);
	hit.textureV = (z - z0) / (z1 - z0);
	hit.length = length;
	hit.pMaterial = pMaterial;
	hit.point = ray.GetPointAtLength(length);
	hit.normal = Vec3(1, 0, 0);

	return true;
}

bool YZRectangle::GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const
{
	float epsilon = 0.0001f;
	box = AABB(Vec3(x - epsilon, y0, z0), Vec3(x + epsilon, y1, z1));
	return true;
}
