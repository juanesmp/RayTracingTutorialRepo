#pragma once

#include "Hitable.h"

class Material
{
public:
	virtual bool Scatter(const Ray& rayIn, const HitRecord& hit, Vec3& attenuation, Ray& scatteredRay) const = 0;
	virtual Vec3 GetEmission(float u, float v, const Vec3 & point) const { return Vec3(0, 0, 0); }
};

