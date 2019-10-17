#pragma once

#include "Material.h"

class LambertianMaterial : public Material
{
public:
	LambertianMaterial(const Vec3& albedo) : albedoColor(albedo) {}
	virtual bool Scatter(const Ray & rayIn, const HitRecord & hit, Vec3 & attenuation, Ray & scatteredRay) const override;

private:
	Vec3 albedoColor;
};

