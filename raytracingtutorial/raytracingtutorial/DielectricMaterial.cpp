#include "pch.h"
#include "DielectricMaterial.h"
#include "Random.h"

bool DielectricMaterial::Scatter(const Ray & rayIn, const HitRecord & hit, Vec3 & attenuation, Ray & scatteredRay) const
{
	attenuation = Vec3(1, 1, 1);

	Vec3 outwardNormal;
	float niOverNt;
	float cosine;
	
	float dotRayNormal = Dot(rayIn.direction, hit.normal);

	if (dotRayNormal > 0)
	{
		outwardNormal = -hit.normal;
		niOverNt = refIdx;
		cosine = refIdx * dotRayNormal / rayIn.direction.GetLength();
	}
	else
	{
		outwardNormal = hit.normal;
		niOverNt = 1.0f / refIdx;
		cosine = -dotRayNormal / rayIn.direction.GetLength();
	}

	Vec3 refractedRay;
	if (Refract(rayIn.direction, outwardNormal, niOverNt, refractedRay) && SchlickProbability(cosine) < GetRandom0To1())
		scatteredRay = Ray(hit.point, refractedRay, rayIn.time);
	else
		scatteredRay = Ray(hit.point, Reflect(rayIn.direction, hit.normal), rayIn.time);

	return true;
}

float DielectricMaterial::SchlickProbability(float cosine) const
{
	float r0 = (1.0f - refIdx) / (1.0f + refIdx);
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * powf(1.0f - cosine, 5);
}
