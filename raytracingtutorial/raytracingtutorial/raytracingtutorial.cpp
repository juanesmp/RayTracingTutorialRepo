// raytracingtutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "Vec3.h"

int main()
{
	int nx = 200;
	int ny = 100;

	std::ofstream ppmFile("image.ppm");
	//ppmFile.open("image.ppm");

	if (ppmFile.is_open())
	{
		ppmFile << "P3\n" << nx << " " << ny << "\n255\n";
		for (int j = ny - 1; j >= 0; j--)
		{
			for (int i = 0; i < nx; i++)
			{
				Vec3 col = Vec3(float(i) / float(nx), float(j) / float(ny), 0.2f);

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


