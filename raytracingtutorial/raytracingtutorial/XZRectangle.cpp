#include "pch.h"
#include "XZRectangle.h"
#include "AABB.h"

bool XZRectangle::DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const
{
	float length = (y - ray.origin.Y()) / ray.direction.Y();
	if (length < minLength || length > maxLength)
		return false;

	float x = ray.origin.X() + length * ray.direction.X();
	if (x < x0 || x > x1)
		return false;

	float z = ray.origin.Z() + length * ray.direction.Z();
	if (z < z0 || z > z1)
		return false;

	hit.textureU = (x - x0) / (x1 - x0);
	hit.textureV = (z - z0) / (z1 - z0);
	hit.length = length;
	hit.pMaterial = pMaterial;
	hit.point = ray.GetPointAtLength(length);
	hit.normal = Vec3(0, 1, 0);

	return true;
}

bool XZRectangle::GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const
{
	float epsilon = 0.0001f;
	box = AABB(Vec3(x0, y - epsilon, z0), Vec3(x1, y + epsilon, z1));
	return true;
}
