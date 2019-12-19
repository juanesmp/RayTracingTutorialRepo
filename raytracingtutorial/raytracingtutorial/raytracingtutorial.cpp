// raytracingtutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "Ray.h"
#include "Hitable.h"
#include "Camera.h"
#include "Material.h"
#include "Scene.h"

struct OutputParams
{
	OutputParams(int quality) 
	{
		switch (quality)
		{
		case 0: // very low
			pixelSizeX = 100;
			pixelSizeY = 70;
			raysPerPixel = 16;
			maxRayBounces = 10;
			break;
		case 1: // low
			pixelSizeX = 250;
			pixelSizeY = 150;
			raysPerPixel = 128;
			maxRayBounces = 50;
			break;
		case 2: // medium
		default:
			pixelSizeX = 400;
			pixelSizeY = 280;
			raysPerPixel = 128;
			maxRayBounces = 50;
			break;
		}	
	};

	int pixelSizeX;
	int pixelSizeY;
	int raysPerPixel;
	int maxRayBounces;
};

Vec3 GetBackgroundColor(const Ray& r)
{
	Vec3 unitDirection = ConvertToUnitVector(r.direction);
	float t = 0.5f * (unitDirection.Y() + 1);
	return (1.0f - t) * Vec3(1, 1, 1) + t * Vec3(0.5f, 0.7f, 1);
}

Vec3 GetColorFromRay(const Ray& ray, Hitable* scene, int bounces, int maxRayBounces)
{
	HitRecord hit;

	if (scene->DoesRayHit(ray, 0.001f, 100000, hit))
	{
		Ray scatteredRay;
		Vec3 attenuation;
		if (bounces < maxRayBounces && hit.pMaterial->Scatter(ray, hit, attenuation, scatteredRay))
			return attenuation * GetColorFromRay(scatteredRay, scene, bounces + 1, maxRayBounces);
		else
			return Vec3(0, 0, 0);
	}
	else
	{
		return GetBackgroundColor(ray);
	}
}

Vec3 CorrectGamma(Vec3& color)
{
	return Vec3(sqrtf(color.R()), sqrtf(color.G()), sqrtf(color.B()));
}

Vec3 GetColorForPixel(int pixelX, int pixelY, Camera* pCamera, Hitable* scene, const OutputParams& outputParams)
{
	Vec3 col(0, 0, 0);

	for (int ray = 0; ray < outputParams.raysPerPixel; ray++)
	{
		float rayOffsetU = (ray % 2 == 0) ? 0.25f : 0.75f;
		float rayOffsetY = (float)ray / (float)outputParams.raysPerPixel;
		
		float u = (float(pixelX) + rayOffsetU) / float(outputParams.pixelSizeX);
		float v = (float(pixelY) + rayOffsetY) / float(outputParams.pixelSizeY);

		Ray r = pCamera->GetRay(u, v);
		col += GetColorFromRay(r, scene, 0, outputParams.maxRayBounces);
	}

	col /= float(outputParams.raysPerPixel);

	return CorrectGamma(col);
}

Camera* CreateCamera(const OutputParams& outputParams, float shutterOpenTime, float shutterCloseTime)
{
	CameraParams p;

	p.position = Vec3(8, 1.5f, 2.5f);
	p.lookAtPoint = Vec3(0, 0, -1);
	p.upVector = Vec3(0, 1, 0);
	p.verticalFOV = 45;
	p.aspectRatio = float(outputParams.pixelSizeX) / float(outputParams.pixelSizeY);
	p.aperture = 0.0001f; // 0.1f
	p.focusDistance = (p.position - p.lookAtPoint).GetLength();
	p.shutterOpenTime = shutterOpenTime;
	p.shutterCloseTime = shutterCloseTime;

	return new Camera(p);
}

int main()
{
	std::ofstream ppmFile("image.ppm");

	if (ppmFile.is_open())
	{
		OutputParams outputParams(1);

		float shutterOpenTime = 0.06f;
		float shutterCloseTime = 0.07f;
		
		Camera* pCamera = CreateCamera(outputParams, shutterOpenTime, shutterCloseTime);
		
		Hitable* scene = CreateScene(shutterOpenTime, shutterCloseTime);

		ppmFile << "P3\n" << outputParams.pixelSizeX << " " << outputParams.pixelSizeY << "\n255\n";

		for (int pixelY = outputParams.pixelSizeY - 1; pixelY >= 0; pixelY--)
		{
			for (int pixelX = 0; pixelX < outputParams.pixelSizeX; pixelX++)
			{
				Vec3 col = GetColorForPixel(pixelX, pixelY, pCamera, scene, outputParams);

				int ir = int(255.99 * col.R());
				int ig = int(255.99 * col.G());
				int ib = int(255.99 * col.B());

				ppmFile << ir << " " << ig << " " << ib << "\n";
			}
		}
	}
	else
	{
		std::cout << "Unable to open file";
	}
}