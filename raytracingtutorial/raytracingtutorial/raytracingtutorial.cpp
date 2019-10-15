// raytracingtutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Ray.h"
#include "raytracingtutorial.h"


float GetRayLenghtToHitSphere(const Vec3& center, float radius, const Ray& ray)
{
	Vec3 oc = ray.origin - center;
	float a = Dot(ray.direction, ray.direction);
	float b = 2.0f * Dot(oc, ray.direction);
	float c = Dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	
	if (discriminant < 0)
		return -1.0f;
	else
		return (-b - sqrtf(discriminant)) / (2.0f * a);
}

Vec3 GetBackgroundColor(const Ray& r)
{
	Vec3 unitDirection = ConvertToUnitVector(r.direction);
	float t = 0.5f * (unitDirection.Y() + 1);
	return (1.0f - t) * Vec3(1, 1, 1) + t * Vec3(0.5f, 0.7f, 1);
}

Vec3 GetColorFromRay(const Ray& ray)
{
	Vec3 sphereCenter = Vec3(0, 0, -1);
	float t = GetRayLenghtToHitSphere(sphereCenter, 0.5f, ray);
	if (t > 0)
	{
		Vec3 normal = ConvertToUnitVector(ray.GetPointAtLenght(t) - sphereCenter);
		return 0.5f * Vec3(normal.X() + 1.0f, normal.Y() + 1.0f, normal.Z() + 1.0f);
	}
	else
	{
		return GetBackgroundColor(ray);
	}
}

int main()
{
	std::ofstream ppmFile("image.ppm");

	if (ppmFile.is_open())
	{
		int nx = 200;
		int ny = 100;
		
		ppmFile << "P3\n" << nx << " " << ny << "\n255\n";

		Vec3 lowerLeftCorner(-2, -1, -1);
		Vec3 horizontal(4, 0, 0);
		Vec3 vertical(0, 2, 0);
		Vec3 origin(0, 0, 0);

		for (int j = ny - 1; j >= 0; j--)
		{
			for (int i = 0; i < nx; i++)
			{
				float u = float(i) / float(nx);
				float v = float(j) / float(ny);
				
				Ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);
				
				Vec3 col = GetColorFromRay(r);

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


