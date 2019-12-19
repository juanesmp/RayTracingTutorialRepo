#pragma once

#include "Material.h"
#include "Texture.h"

class LambertianMaterial : public Material
{
public:
	LambertianMaterial(Texture* albedo) : pAlbedo(albedo) {}
	virtual bool Scatter(const Ray & rayIn, const HitRecord & hit, Vec3 & attenuation, Ray & scatteredRay) const override;

private:
	Texture* pAlbedo;
};

