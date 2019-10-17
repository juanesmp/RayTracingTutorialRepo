#include "pch.h"
#include "DielectricMaterial.h"

bool DielectricMaterial::Scatter(const Ray & rayIn, const HitRecord & hit, Vec3 & attenuation, Ray & scatteredRay) const
{
	Vec3 outwardNormal;
	Vec3 reflected = Reflect(rayIn.direction, hit.normal);
	float niOverNt;
	Vec3 refracted;

	attenuation = Vec3(1, 1, 1);

	if (Dot(rayIn.direction, hit.normal) > 0)
	{
		outwardNormal = -hit.normal;
		niOverNt = refIdx;
	}
	else
	{
		outwardNormal = hit.normal;
		niOverNt = 1.0f / refIdx;
	}

	if (Refract(rayIn.direction, outwardNormal, niOverNt, refracted))
		scatteredRay = Ray(hit.point, refracted);
	else
		scatteredRay = Ray(hit.point, reflected);

	return true;
}
