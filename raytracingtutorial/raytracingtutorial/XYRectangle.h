#pragma once
#include "Hitable.h"

class XYRectangle :	public Hitable
{
public:
	XYRectangle() {}
	XYRectangle(float _x0, float _x1, float _y0, float _y1, float _z, Material* material) : 
		x0(_x0), x1(_x1), y0(_y0), y1(_y1), z(_z), pMaterial(material) {}

	virtual bool DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const override;
	virtual bool GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const override;

private:
	Material* pMaterial;
	float x0, x1, y0, y1, z;
};

