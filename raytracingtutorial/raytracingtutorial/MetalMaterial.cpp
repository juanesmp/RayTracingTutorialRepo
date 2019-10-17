#include "pch.h"
#include "MetalMaterial.h"
#include "Random.h"

bool MetalMaterial::Scatter(const Ray & rayIn, const HitRecord & hit, Vec3 & attenuation, Ray & scatteredRay) const
{
	Vec3 reflected = Reflect(ConvertToUnitVector(rayIn.direction), hit.normal);
	scatteredRay = Ray(hit.point, reflected + fuzzyness * GetRandomVec3InUnitSphere());
	attenuation = albedoColor;
	return Dot(scatteredRay.direction, hit.normal) > 0;
}
