#pragma once

#include "Material.h"
#include "Texture.h"

class MetalMaterial : public Material
{
public:
	MetalMaterial(Texture* albedo, float fuzz) : pAlbedo(albedo) 
	{
		if (fuzz < 1.0f)
			fuzzyness = fuzz;
		else
			fuzzyness = 1;
	}

	virtual bool Scatter(const Ray & rayIn, const HitRecord & hit, Vec3 & attenuation, Ray & scatteredRay) const override;

private:
	Texture* pAlbedo;
	float fuzzyness;
};

