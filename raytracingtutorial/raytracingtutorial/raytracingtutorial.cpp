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

int main()
{
	std::ofstream ppmFile("image.ppm");

	if (ppmFile.is_open())
	{
		int outputSizeX = 400;
		int oputputSizeY = 200;
		
		ppmFile << "P3\n" << outputSizeX << " " << oputputSizeY << "\n255\n";

		Vec3 vpLowerLeftCorner(-2, -1, -1);
		Vec3 vpHorizontal(4, 0, 0);
		Vec3 vpVertical(0, 2, 0);
		
		Vec3 cameraPosition(0, 0, 0);

		Hitable* list[2];
		list[0] = new Sphere(Vec3(0, 0, -1), 0.5f);
		list[1] = new Sphere(Vec3(0, -100.5f, -1), 100);
		Hitable* scene = new HitableList(list, 2);

		for (int j = oputputSizeY - 1; j >= 0; j--)
		{
			for (int i = 0; i < outputSizeX; i++)
			{
				float u = float(i) / float(outputSizeX);
				float v = float(j) / float(oputputSizeY);
				
				Ray r(cameraPosition, vpLowerLeftCorner + u * vpHorizontal + v * vpVertical);
				
				Vec3 col = GetColorFromRay(r, scene);

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


