#pragma once

#include "Ray.h"

class Camera
{
public:
	Camera();

	Ray GetRay(float screenU, float screenV);

	Vec3 position;

	Vec3 vpLowerLeftCorner;
	Vec3 vpHorizontal;
	Vec3 vpVertical;
};

