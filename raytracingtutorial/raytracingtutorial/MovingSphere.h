#pragma once
#include "Hitable.h"

class MovingSphere : public Hitable
{
public:
	MovingSphere(Vec3 _center0, Vec3 _center1, float _time0, float _time1, float _radius, Material* pMtrl) : 
		center0(_center0), center1(_center1), time0(_time0), time1(_time1), radius(_radius), pMaterial(pMtrl) {};

	virtual bool DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const override;
	virtual bool GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const override;

private:
	Vec3 GetCenterAtTime(float time) const;
	void FillHitRecord(float length, const Ray & ray, HitRecord & hit) const;

	Vec3 center0, center1;
	float time0, time1;
	float radius;
	Material* pMaterial;
};

