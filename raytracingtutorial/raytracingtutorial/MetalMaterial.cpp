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

Vec3 MetalMaterial::Reflect(const Vec3 & v, const Vec3 & normal) const
{
	return v - 2.0f * Dot(v, normal) * normal;
}
