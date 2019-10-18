// raytracingtutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "Ray.h"
#include "Hitable.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include "Material.h"
#include "LambertianMaterial.h"
#include "MetalMaterial.h"
#include "DielectricMaterial.h"
#include "Random.h"

struct OutputParams
{
	int pixelSizeX = 400; // 400;
	int pixelSizeY = 280; // 200;
	int raysPerPixel = 128; // 64;
	int maxRayBounces = 50; //50;
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

	if (scene->DoesHit(ray, 0.001f, 100000, hit))
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

Hitable* CreateScene()
{
	int sphereCount = 500;

	Hitable** list = new Hitable*[sphereCount + 1];
	list[0] = new Sphere(Vec3(0, -1000, 0), 1000, new LambertianMaterial(Vec3(0.5f, 0.5f, 0.5f)));

	int i = 1;

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float chooseMtrl = GetRand0To1();
			Vec3 center(a + 0.9f * GetRand0To1(), 0.2f, b + 0.9f * GetRand0To1());
			if ((center - Vec3(4, 0.2f, 0)).GetLength() > 0.9f)
			{
				Material* pMaterial;
				if (chooseMtrl < 0.8f)
				{
					Vec3 albedo(GetRand0To1() * GetRand0To1(), GetRand0To1() * GetRand0To1(), GetRand0To1() * GetRand0To1());
					pMaterial = new LambertianMaterial(albedo);
				}
				else if (chooseMtrl < 0.95f)
				{
					Vec3 albedo(0.5f * (1.0f + GetRand0To1()), 0.5f * (1.0f + GetRand0To1()), 0.5f * (1.0f + GetRand0To1()));
					pMaterial = new MetalMaterial(albedo, 0.5f * GetRand0To1());
				}
				else
				{
					pMaterial = new DielectricMaterial(1.5f);
				}
				list[i++] = new Sphere(center, 0.2f, pMaterial);
			}
		}
	}

	list[i++] = new Sphere(Vec3(0, 1, 0), 1.0f, new DielectricMaterial(1.5f));
	list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0f, new LambertianMaterial(Vec3(0.4f, 0.2f, 0.1f)));
	list[i++] = new Sphere(Vec3(4, 1, 0), 1.0f, new MetalMaterial(Vec3(0.7f, 0.6f, 0.5f), 0));

	return new HitableList(list, i);
}

Camera* CreateCamera(const OutputParams& outputParams)
{
	CameraParams p;

	p.position = Vec3(8, 1.5f, 2.5f);
	p.lookAtPoint = Vec3(0, 0, -1);
	p.upVector = Vec3(0, 1, 0);
	p.verticalFOV = 45;
	p.aspectRatio = float(outputParams.pixelSizeX) / float(outputParams.pixelSizeY);
	p.aperture = 0.1f;
	p.focusDistance = (p.position - p.lookAtPoint).GetLength();

	return new Camera(p);
}

int main()
{
	std::ofstream ppmFile("image.ppm");

	if (ppmFile.is_open())
	{
		OutputParams outputParams;
		Camera* pCamera = CreateCamera(outputParams);
		Hitable* scene = CreateScene();

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