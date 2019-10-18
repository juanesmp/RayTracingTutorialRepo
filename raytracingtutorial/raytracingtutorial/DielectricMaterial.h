#pragma once

#include "Material.h"

class DielectricMaterial : public Material
{
public:
	DielectricMaterial(float ri) : refIdx(ri) {}
	virtual bool Scatter(const Ray & rayIn, const HitRecord & hit, Vec3 & attenuation, Ray & scatteredRay) const override;

private:
	float SchlickProbability(float cosine) const;
	float refIdx;
};

