#include "pch.h"
#include "Camera.h"
#include "Random.h"

#define _USE_MATH_DEFINES
#include <math.h>

Camera::Camera(const CameraParams& params)
{
	position = params.position;
	lensRadius = params.aperture / 2.0f;

	float theta = params.verticalFOV * float(M_PI) / 180.0f;
	float halfHeight = tanf(theta / 2.0f);
	float halfWidth = params.aspectRatio * halfHeight;

	Vec3 w = ConvertToUnitVector(position - params.lookAtPoint);
	uAxis = ConvertToUnitVector(Cross(params.upVector, w));
	vAxis = Cross(w, uAxis);

	float fd = params.focusDistance;

	vpLowerLeftCorner = position - halfWidth * fd * uAxis - halfHeight * fd * vAxis - fd * w;
	vpHorizontal = 2.0f * halfWidth * fd * uAxis;
	vpVertical = 2.0f * halfHeight * fd * vAxis;

	shutterOpenTime = params.shutterOpenTime;
	shutterOpenDuration = params.shutterCloseTime - params.shutterOpenTime;
}

Ray Camera::GetRay(float screenU, float screenV)
{
	Vec3 offset = lensRadius * GetRandomVec3InUnitDisk();
	offset = uAxis * offset.X() + vAxis * offset.Y();
	
	Vec3 rayStart = position + offset;
	float time = shutterOpenTime + GetRandom0To1() * shutterOpenDuration;
	Vec3 direction = vpLowerLeftCorner + screenU * vpHorizontal + screenV * vpVertical - rayStart;
	
	return Ray(rayStart, direction, time);
}

