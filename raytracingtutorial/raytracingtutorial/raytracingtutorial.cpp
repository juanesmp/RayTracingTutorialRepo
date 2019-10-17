// raytracingtutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include "Material.h"
#include "LambertianMaterial.h"
#include "MetalMaterial.h"

struct OutputParams
{
	int pixelSizeX = 400;
	int pixelSizeY = 200;
	int raysPerPixel = 64;
};

Vec3 GetBackgroundColor(const Ray& r)
{
	Vec3 unitDirection = ConvertToUnitVector(r.direction);
	float t = 0.5f * (unitDirection.Y() + 1);
	return (1.0f - t) * Vec3(1, 1, 1) + t * Vec3(0.5f, 0.7f, 1);
}

Vec3 GetColorFromRay(const Ray& ray, Hitable* scene, int depth)
{
	HitRecord hit;

	if (scene->DoesHit(ray, 0.001f, 100000, hit))
	{
		Ray scatteredRay;
		Vec3 attenuation;
		if (depth < 50 && hit.pMaterial->Scatter(ray, hit, attenuation, scatteredRay))
			return attenuation * GetColorFromRay(scatteredRay, scene, depth + 1);
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

Vec3 GetColorForPixel(int pixelX, int pixelY, Camera camera, Hitable* scene, const OutputParams& outputParams)
{
	Vec3 col(0, 0, 0);

	for (int ray = 0; ray < outputParams.raysPerPixel; ray++)
	{
		float rayOffsetU = (ray % 2 == 0) ? 0.25f : 0.75f;
		float rayOffsetY = (float)ray / (float)outputParams.raysPerPixel;
		
		float u = (float(pixelX) + rayOffsetU) / float(outputParams.pixelSizeX);
		float v = (float(pixelY) + rayOffsetY) / float(outputParams.pixelSizeY);

		Ray r = camera.GetRay(u, v);
		col += GetColorFromRay(r, scene, 0);
	}

	col /= float(outputParams.raysPerPixel);

	return CorrectGamma(col);
}

int main()
{
	std::ofstream ppmFile("image.ppm");

	if (ppmFile.is_open())
	{
		OutputParams outputParams;
		
		ppmFile << "P3\n" << outputParams.pixelSizeX << " " << outputParams.pixelSizeY << "\n255\n";

		Camera camera;

		Hitable* list[4];
		
		list[0] = new Sphere(Vec3(0, 0, -1),       0.5f, new LambertianMaterial(Vec3(0.8f, 0.3f, 0.3f)));
		list[1] = new Sphere(Vec3(0, -100.5f, -1), 100,  new LambertianMaterial(Vec3(0.8f, 0.8f, 0.0f)));
		list[2] = new Sphere(Vec3(1, 0, -1),       0.5f, new MetalMaterial(Vec3(0.8f, 0.6f, 0.2f)));
		list[3] = new Sphere(Vec3(-1, 0, -1),      0.5f, new MetalMaterial(Vec3(0.8f, 0.8f, 0.8f)));

		Hitable* scene = new HitableList(list, 4);

		for (int pixelY = outputParams.pixelSizeY - 1; pixelY >= 0; pixelY--)
		{
			for (int pixelX = 0; pixelX < outputParams.pixelSizeX; pixelX++)
			{
				Vec3 col = GetColorForPixel(pixelX, pixelY, camera, scene, outputParams);

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