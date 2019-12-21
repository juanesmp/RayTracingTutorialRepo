#include "pch.h"
#include "RotateY.h"

#define _USE_MATH_DEFINES
#include <math.h>

RotateY::RotateY(Hitable* child, float angle) : pChild(child)
{
	float radians = (float(M_PI) / 180.0f) * angle;

	sinTheta = sinf(radians);
	cosTheta = cosf(radians);

	hasBox = pChild->GetBoundingBoxAtTime(0, 1, aabb);

	Vec3 min(1000000, 1000000, 1000000);
	Vec3 max(-1000000, -1000000, -1000000);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				float x = i * aabb.GetMax().X() + (1 - i) * aabb.GetMin().X();
				float y = j * aabb.GetMax().Y() + (1 - j) * aabb.GetMin().Y();
				float z = k * aabb.GetMax().Z() + (1 - k) * aabb.GetMin().Z();

				float newX = cosTheta * x + sinTheta * z;
				float newZ = -sinTheta * x + cosTheta * z;

				Vec3 tester(newX, y, newZ);

				for (int c = 0; c < 3; c++)
				{
					if (tester.e[c] > max.e[c])
						max.e[c] = tester.e[c];
					
					if (tester.e[c] < min.e[c])
						min.e[c] = tester.e[c];
				}
			}
		}
	}

	aabb = AABB(min, max);
}

bool RotateY::DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const
{
	Vec3 origin = ray.origin;
	Vec3 direction = ray.direction;

	origin.e[0] = cosTheta * ray.origin.e[0] - sinTheta * ray.origin.e[2];
	origin.e[2] = sinTheta * ray.origin.e[0] + cosTheta * ray.origin.e[2];

	direction.e[0] = cosTheta * ray.direction.e[0] - sinTheta * ray.direction.e[2];
	direction.e[2] = sinTheta * ray.direction.e[0] + cosTheta * ray.direction.e[2];

	Ray rotatedRay(origin, direction, ray.time);

	if (pChild->DoesRayHit(rotatedRay, minLength, maxLength, hit))
	{
		Vec3 point = hit.point;
		Vec3 normal = hit.normal;

		point.e[0] = cosTheta * hit.point.e[0] + sinTheta * hit.point.e[2];
		point.e[2] = -sinTheta * hit.point.e[0] + cosTheta * hit.point.e[2];

		normal.e[0] = cosTheta * hit.point.e[0] + sinTheta * hit.normal.e[2];
		normal.e[2] = -sinTheta * hit.point.e[0] + cosTheta * hit.normal.e[2];

		hit.point = point;
		hit.normal = normal;

		return true;
	}

	return false;
}

bool RotateY::GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const
{
	box = aabb;
	return hasBox;
}
