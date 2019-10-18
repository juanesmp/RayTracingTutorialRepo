#pragma once

#include "Ray.h"

class Camera
{
public:
	Camera(const Vec3& position, const Vec3& lookAtPoint, const Vec3& upVector, float verticalFOV, float aspect);

	Ray GetRay(float screenU, float screenV);

private:
	Vec3 position;

	Vec3 vpLowerLeftCorner;
	Vec3 vpHorizontal;
	Vec3 vpVertical;
};

