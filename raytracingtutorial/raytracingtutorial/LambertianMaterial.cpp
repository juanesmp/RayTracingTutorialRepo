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

Vec3 LambertianMaterial::GetRandomVec3InUnitSphere() const
{
	Vec3 p;
	do
	{
		p = 2.0f * Vec3(GetRand0To1(), GetRand0To1(), GetRand0To1()) - Vec3(1, 1, 1);
	} while (p.GetSquaredLength() >= 1.0f);

	return p;
}