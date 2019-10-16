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

struct OutputParams
{
	int pixelSizeX = 400;
	int pixelSizeY = 200;
	int aaSampleCount = 8;
};

Vec3 GetBackgroundColor(const Ray& r)
{
	Vec3 unitDirection = ConvertToUnitVector(r.direction);
	float t = 0.5f * (unitDirection.Y() + 1);
	return (1.0f - t) * Vec3(1, 1, 1) + t * Vec3(0.5f, 0.7f, 1);
}

Vec3 GetColorFromRay(const Ray& ray, Hitable* scene)
{
	HitRecord hit;

	if (scene->DoesHit(ray, 0, 100000, hit))
		return 0.5f * Vec3(hit.normal.X() + 1.0f, hit.normal.Y() + 1.0f, hit.normal.Z() + 1.0f);
	else
		return GetBackgroundColor(ray);
}

Vec3 GetColor(int pixelX, int pixelY, Camera camera, Hitable* scene, const OutputParams& outputParams)
{
	Vec3 col(0, 0, 0);
	for (int sample = 0; sample < outputParams.aaSampleCount; sample++)
	{
		float u = float(pixelX + ((float)sample / (float)outputParams.aaSampleCount)) / float(outputParams.pixelSizeX);
		float v = float(pixelY + ((float)sample / (float)outputParams.aaSampleCount)) / float(outputParams.pixelSizeY);

		Ray r = camera.GetRay(u, v);
		col += GetColorFromRay(r, scene);
	}
	col /= float(outputParams.aaSampleCount);

	return col;
}

int main()
{
	std::ofstream ppmFile("image.ppm");

	if (ppmFile.is_open())
	{
		OutputParams outputParams;
		
		ppmFile << "P3\n" << outputParams.pixelSizeX << " " << outputParams.pixelSizeY << "\n255\n";

		Camera camera;

		Hitable* list[2];
		list[0] = new Sphere(Vec3(0, 0, -1), 0.5f);
		list[1] = new Sphere(Vec3(0, -100.5f, -1), 100);
		Hitable* scene = new HitableList(list, 2);

		for (int pixelY = outputParams.pixelSizeY - 1; pixelY >= 0; pixelY--)
		{
			for (int pixelX = 0; pixelX < outputParams.pixelSizeX; pixelX++)
			{
				Vec3 col = GetColor(pixelX, pixelY, camera, scene, outputParams);

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


