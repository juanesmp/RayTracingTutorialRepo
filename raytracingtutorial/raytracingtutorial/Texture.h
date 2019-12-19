#pragma once
#include "Vec3.h"

class Texture
{
public:
	virtual Vec3 Sample(float u, float v, const Vec3 &point) const = 0;
};