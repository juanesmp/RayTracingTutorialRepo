#include "pch.h"
#include "Camera.h"

#define _USE_MATH_DEFINES
#include <math.h>

Camera::Camera(const Vec3& pos, const Vec3& lookAtPoint, const Vec3& upVector, float verticalFOV, float aspect)
{
	position = pos;

	float theta = verticalFOV * float(M_PI) / 180.0f;
	float halfHeight = tanf(theta / 2.0f);
	float halfWidth = aspect * halfHeight;

	Vec3 w = ConvertToUnitVector(position - lookAtPoint);
	Vec3 u = ConvertToUnitVector(Cross(upVector, w));
	Vec3 v = Cross(w, u);

	vpLowerLeftCorner = position - halfWidth * u - halfHeight * v - w;
	vpHorizontal = 2.0f * halfWidth * u;
	vpVertical = 2.0f * halfHeight * v;
}

Ray Camera::GetRay(float screenU, float screenV)
{
	return Ray(position, vpLowerLeftCorner + screenU * vpHorizontal + screenV * vpVertical - position);
}

