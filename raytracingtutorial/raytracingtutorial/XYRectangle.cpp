#include "pch.h"
#include "XYRectangle.h"
#include "AABB.h"

bool XYRectangle::DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const
{
	float length = (z - ray.origin.Z()) / ray.direction.Z();
	if (length < minLength || length > maxLength)
		return false;

	float x = ray.origin.X() + length * ray.direction.X();
	if (x < x0 || x > x1)
		return false;

	float y = ray.origin.Y() + length * ray.direction.Y();
	if (y < y0 || y > y1)
		return false;

	hit.textureU = (x - x0) / (x1 - x0);
	hit.textureV = (y - y0) / (y1 - y0);
	hit.length = length;
	hit.pMaterial = pMaterial;
	hit.point = ray.GetPointAtLength(length);
	hit.normal = Vec3(0, 0, 1);

	return true;
}

bool XYRectangle::GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const
{
	float epsilon = 0.0001f;
	box = AABB(Vec3(x0, y0, z - epsilon), Vec3(x1, y1, z + epsilon));
	return true;
}
