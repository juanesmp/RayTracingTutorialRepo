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
			raysPerPixel = 32;
			maxRayBounces = 10;
			break;
		case 1: // low
			pixelSizeX = 200;
			pixelSizeY = 120;
			raysPerPixel = 128;
			maxRayBounces = 50;
			break;
		case 2: // medium
		default:
			pixelSizeX = 400;
			pixelSizeY = 280;
			raysPerPixel = 256;
			maxRayBounces = 50;
			break;
		}	
	};

	int pixelSizeX;
	int pixelSizeY;
	int raysPerPixel;
	int maxRayBounces;
};

Vec3 GetColorFromRay(const Ray& ray, Hitable* scene, int bounces, int maxRayBounces)
{
	HitRecord hit;

	if (scene->DoesRayHit(ray, 0.001f, 100000, hit))
	{
		Ray scatteredRay;
		Vec3 attenuation;
		Vec3 emission = hit.pMaterial->GetEmission(hit.textureU, hit.textureV, hit.point);
		if (bounces < maxRayBounces && hit.pMaterial->Scatter(ray, hit, attenuation, scatteredRay))
			return emission + attenuation * GetColorFromRay(scatteredRay, scene, bounces + 1, maxRayBounces);
		else
			return emission;
	}
	else
	{
		return GetBackgroundColor(ray, 2);
	}
}

Vec3 CorrectGamma(Vec3& color)
{
	return Vec3(sqrtf(color.R()), sqrtf(color.G()), sqrtf(color.B()));
}

Vec3 GetColorForPixel(int pixelX, int pixelY, Camera* pCamera, Hitable* scene, const OutputParams& outputParams)
{
	Vec3 col(0, 0, 0);

	int mod = int(sqrtf(float(outputParams.raysPerPixel)));

	for (int ray = 0; ray < outputParams.raysPerPixel; ray++)
	{
		float rayOffsetU = float(ray % mod) / float(mod);		
		float rayOffsetY = float(ray) / float(outputParams.raysPerPixel);
		//float rayOffsetU = GetRandom0To1();		
		//float rayOffsetY = GetRandom0To1();
		
		float u = (float(pixelX) + rayOffsetU) / float(outputParams.pixelSizeX);
		float v = (float(pixelY) + rayOffsetY) / float(outputParams.pixelSizeY);

		Ray r = pCamera->GetRay(u, v);
		col += GetColorFromRay(r, scene, 0, outputParams.maxRayBounces);
	}

	col /= float(outputParams.raysPerPixel);

	return CorrectGamma(col);
}

Camera* CreateCamera(const OutputParams& outputParams, float shutterOpenTime, float shutterCloseTime, int camSetup)
{
	CameraParams p;

	switch (camSetup)
	{
	case 0:
		p.position = Vec3(8, 1.5f, 2.5f);
		p.lookAtPoint = Vec3(0, 0, -1);
		p.upVector = Vec3(0, 1, 0);
		p.verticalFOV = 45;
		p.aperture = 0.0001f; // 0.1f
		break;
	case 1: // Cornell box
	default:
		p.position = Vec3(278, 278, -800);
		p.lookAtPoint = Vec3(278, 278, 0);
		p.upVector = Vec3(0, 1, 0);
		p.verticalFOV = 40;
		p.aperture = 0.0001f; // 0.1f
		break;
	}

	p.aspectRatio = float(outputParams.pixelSizeX) / float(outputParams.pixelSizeY);
	p.shutterOpenTime = shutterOpenTime;
	p.shutterCloseTime = shutterCloseTime;
	p.focusDistance = (p.position - p.lookAtPoint).GetLength();

	return new Camera(p);
}

int main()
{
	std::ofstream ppmFile("image.ppm");

	if (ppmFile.is_open())
	{
		OutputParams outputParams(0);

		float shutterOpenTime = 0.06f;
		float shutterCloseTime = 0.07f;
		
		Camera* pCamera = CreateCamera(outputParams, shutterOpenTime, shutterCloseTime, 1);
		
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