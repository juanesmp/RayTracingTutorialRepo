#pragma once
#include "Material.h"
#include "Texture.h"

class DiffuseLightMaterial : public Material
{
public:
	DiffuseLightMaterial() {}
	DiffuseLightMaterial(Texture* emission) : pEmission(emission) {}

	virtual bool Scatter(const Ray & rayIn, const HitRecord & hit, Vec3 & attenuation, Ray & scatteredRay) const override;
	virtual Vec3 GetEmission(float u, float v, const Vec3 & point) const override { return pEmission->Sample(u, v, point); }

private:
	Texture* pEmission;
};