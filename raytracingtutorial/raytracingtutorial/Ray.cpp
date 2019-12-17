#include "pch.h"
#include "Ray.h"

Ray::Ray(const Vec3 & _origin, const Vec3 & _direction, float _time)
{
	origin = _origin;
	direction = _direction;
	time = _time;
}

