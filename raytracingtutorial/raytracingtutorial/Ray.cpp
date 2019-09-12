#include "pch.h"
#include "Ray.h"

Ray::Ray()
{
}

Ray::Ray(const Vec3 & _origin, const Vec3 & _direction)
{
	origin = _origin;
	direction = _direction;
}

