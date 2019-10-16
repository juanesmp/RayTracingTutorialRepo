#include "pch.h"
#include "Camera.h"

Camera::Camera()
{
	position = Vec3(0, 0, 0);
	vpLowerLeftCorner = Vec3(-2, -1, -1);
	vpHorizontal = Vec3(4, 0, 0);
	vpVertical = Vec3(0, 2, 0);
}

Ray Camera::GetRay(float screenU, float screenV)
{
	return Ray(position, vpLowerLeftCorner + screenU * vpHorizontal + screenV * vpVertical - position);
}

