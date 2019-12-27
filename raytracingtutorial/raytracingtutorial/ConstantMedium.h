#pragma once
#include "Hitable.h"
#include "Texture.h"
#include "IsotropicMaterial.h"

class ConstantMedium : public Hitable
{
public:
	ConstantMedium(Hitable * boundary, float _density, Texture * albedo) : pBoundary(boundary), density(_density) 
	{
		pMaterial = new IsotropicMaterial(albedo);
	}

	virtual bool DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const override;
	virtual bool GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const override;

private:
	Hitable* pBoundary;
	float density;
	Material * pMaterial;
};

