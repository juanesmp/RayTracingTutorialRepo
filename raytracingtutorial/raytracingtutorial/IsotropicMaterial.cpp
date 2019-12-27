#include "pch.h"
#include "IsotropicMaterial.h"
#include "Random.h"
#include "Ray.h"

bool IsotropicMaterial::Scatter(const Ray & rayIn, const HitRecord & hit, Vec3 & attenuation, Ray & scatteredRay) const
{
	scatteredRay = Ray(hit.point, GetRandomVec3InUnitSphere(), rayIn.time);
	attenuation = pAlbedo->Sample(hit.textureU, hit.textureV, hit.point);
	return true;
}
