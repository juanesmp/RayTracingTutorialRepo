// raytracingtutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Ray.h"

Vec3 GetColorFromRay(const Ray& r)
{
	Vec3 unitDirection = ConvertToUnitVector(r.direction);
	return Vec3(unitDirection.X(), 0, 0);
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


