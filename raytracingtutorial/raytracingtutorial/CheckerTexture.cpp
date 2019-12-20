#include "pch.h"
#include <stdlib.h>
#include "CheckerTexture.h"

Vec3 CheckerTexture::Sample(float u, float v, const Vec3 & point) const
{
	float sines = sinf(10*point.X()) * sinf(10 * point.Y()) * sinf(10 * point.Z());
	return sines < 0 ? pOddTexture->Sample(u, v, point) : pEvenTexture->Sample(u, v, point);
}
