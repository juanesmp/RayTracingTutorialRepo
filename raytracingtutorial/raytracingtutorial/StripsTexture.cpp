#include "pch.h"
#include "StripsTexture.h"

Vec3 StripsTexture::Sample(float u, float v, const Vec3 & point) const
{
	float sines = sinf(3 * point.Y()) * sinf(3 * point.Z());
	return sines < 0 ? pOddTexture->Sample(u, v, point) : pEvenTexture->Sample(u, v, point);
}

