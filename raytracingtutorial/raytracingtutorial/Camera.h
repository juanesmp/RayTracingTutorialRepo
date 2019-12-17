#pragma once

#include "Ray.h"

struct CameraParams
{
	Vec3 position;
	Vec3 lookAtPoint;
	Vec3 upVector;
	float verticalFOV;
	float aspectRatio;
	float aperture;
	float focusDistance;
	float shutterOpenTime;
	float shutterCloseTime;
};

class Camera
{
public:
	Camera(const CameraParams& params);

	Ray GetRay(float screenU, float screenV);

private:
	Vec3 position;

	Vec3 vpLowerLeftCorner;
	Vec3 vpHorizontal;
	Vec3 vpVertical;

	Vec3 uAxis, vAxis;
	float lensRadius;

	float shutterOpenTime;
	float shutterOpenDuration;
};

