#pragma once
#include "Material.h"
#include "Texture.h"

class IsotropicMaterial : public Material
{
public:
	IsotropicMaterial(Texture * albedo) : pAlbedo(albedo) {}
	virtual bool Scatter(const Ray & rayIn, const HitRecord & hit, Vec3 & attenuation, Ray & scatteredRay) const override;

private:
	Texture * pAlbedo;
};

