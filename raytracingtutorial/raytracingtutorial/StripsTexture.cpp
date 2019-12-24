#include "pch.h"
#include "StripsTexture.h"

Vec3 StripsTexture::Sample(float u, float v, const Vec3 & point) const
{
	bool even = (int(u * 24) % 2 == 0);
	return even ? pEvenTexture->Sample(u, v, point) : pOddTexture->Sample(u, v, point);
}

