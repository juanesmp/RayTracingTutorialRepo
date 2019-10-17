#include "pch.h"
#include "LambertianMaterial.h"
#include "Random.h"

bool LambertianMaterial::Scatter(const Ray & rayIn, const HitRecord & hit, Vec3 & attenuation, Ray & scatteredRay) const
{
	Vec3 target = hit.point + hit.normal + GetRandomVec3InUnitSphere();
	scatteredRay = Ray(hit.point, target - hit.point);
	attenuation = albedoColor;
	return true;
}

