#include "pch.h"
#include "SphereUtils.h"
#include "AABB.h"

#define _USE_MATH_DEFINES
#include <math.h>

void GetSpehereTextureUV(const Vec3 & point, float & u, float & v)
{
	float phi = float(atan2(point.Z(), point.X()));
	float theta = float(asin(point.Y()));
	float PI = float(M_PI);

	u = 1 - (phi + PI) / (2.0f * PI);
	v = (theta + PI / 2.0f) / PI;
}

AABB GetSphereBoundingBox(Vec3 center, float radius)
{
	Vec3 radiusVec = Vec3(radius, radius, radius);
	return AABB(center - radiusVec, center + radiusVec);
}
