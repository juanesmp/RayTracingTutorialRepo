#pragma once

#include "Hitable.h"

class Material
{
public:
	virtual bool Scatter(const Ray& rayIn, const HitRecord& hit, Vec3& attenuation, Ray& scatteredRay) const = 0;
};

