#pragma once
#include "Vec3.h"
#include "Ray.h"
#include "FloatUtils.h"

class AABB
{
public:
	AABB() {};
	AABB(const Vec3 _min, const Vec3 _max) { min = _min; max = _max; }

	bool DoesRayHit(const Ray& ray, float minLength, float maxLength) const;

	Vec3 GetMin() const { return min; }
	Vec3 GetMax() const { return max; }

private:
	Vec3 min;
	Vec3 max;
};

inline AABB CombineAABBs(AABB& a, AABB& b)
{
	Vec3 min(GetMinFloat(a.GetMin().X(), b.GetMin().X()), GetMinFloat(a.GetMin().Y(), b.GetMin().Y()), GetMinFloat(a.GetMin().Z(), b.GetMin().Z()));
	Vec3 max(GetMaxFloat(a.GetMax().X(), b.GetMax().X()), GetMaxFloat(a.GetMax().Y(), b.GetMax().Y()), GetMaxFloat(a.GetMax().Z(), b.GetMax().Z()));
	return AABB(min, max);
}