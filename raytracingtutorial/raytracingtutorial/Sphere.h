#pragma once
#include "Hitable.h"

class Sphere : public Hitable
{
public:
	Sphere() {};
	Sphere(Vec3 cen, float rad, Material* pMtrl) : center(cen), radius(rad), pMaterial(pMtrl) {};

	virtual bool DoesHit(const Ray& ray, float minLength, float maxLength, HitRecord& hit) const override;

private:
	void FillHitRecord(float length, const Ray & ray, HitRecord & hit) const;

	Vec3 center;
	float radius;
	Material* pMaterial;
};

