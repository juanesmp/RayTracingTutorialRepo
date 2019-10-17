#pragma once

#include "Material.h"

class MetalMaterial : public Material
{
public:
	MetalMaterial(const Vec3& albedo, float fuzz) : albedoColor(albedo) 
	{
		if (fuzz < 1.0f)
			fuzzyness = fuzz;
		else
			fuzzyness = 1;
	}

	virtual bool Scatter(const Ray & rayIn, const HitRecord & hit, Vec3 & attenuation, Ray & scatteredRay) const override;

private:
	Vec3 Reflect(const Vec3& v, const Vec3& normal) const;
	Vec3 albedoColor;
	float fuzzyness;
};

