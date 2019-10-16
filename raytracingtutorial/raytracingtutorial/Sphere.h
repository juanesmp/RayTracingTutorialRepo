#pragma once
#include "Hitable.h"

class Sphere : public Hitable
{
public:
	Sphere() {};
	Sphere(Vec3 cen, float rad) : center(cen), radius(rad) {};

	virtual bool DoesHit(const Ray& ray, float minLenght, float maxLenght, HitRecord& hit) const override;

	Vec3 center;
	float radius;

private:
	void FillHitRecord(float length, const Ray & ray, HitRecord & hit) const;
};

