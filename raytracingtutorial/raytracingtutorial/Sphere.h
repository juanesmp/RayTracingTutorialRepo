#pragma once
#include "Hitable.h"

class Sphere : public Hitable
{
public:
	Sphere() {};
	Sphere(Vec3 _center, float _radius, Material* pMtrl) : center(_center), radius(_radius), pMaterial(pMtrl) {};

	virtual bool DoesHit(const Ray& ray, float minLength, float maxLength, HitRecord& hit) const override;

private:
	void FillHitRecord(float length, const Ray & ray, HitRecord & hit) const;

	Vec3 center;
	float radius;
	Material* pMaterial;
};

