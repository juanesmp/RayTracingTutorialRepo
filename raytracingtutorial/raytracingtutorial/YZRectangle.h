#pragma once
#include "Hitable.h"

class YZRectangle : public Hitable
{
public:
	YZRectangle() {}
	YZRectangle(float _y0, float _y1, float _z0, float _z1, float _x, Material* material) :
		y0(_y0), y1(_y1), z0(_z0), z1(_z1), x(_x), pMaterial(material) {}

	virtual bool DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const override;
	virtual bool GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const override;

private:
	Material* pMaterial;
	float z0, z1, y0, y1, x;
};

