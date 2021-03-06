#pragma once
#include "Hitable.h"

class XZRectangle :	public Hitable
{
public:
	XZRectangle() {}
	XZRectangle(float _x0, float _x1, float _z0, float _z1, float _y, Material* material) :
		x0(_x0), x1(_x1), z0(_z0), z1(_z1), y(_y), pMaterial(material) {}

	virtual bool DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const override;
	virtual bool GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const override;

private:
	Material* pMaterial;
	float x0, x1, z0, z1, y;
};

