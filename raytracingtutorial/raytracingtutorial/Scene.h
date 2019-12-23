#pragma once
#include "Sphere.h"
#include "MovingSphere.h"
#include "HitableList.h"
#include "LambertianMaterial.h"
#include "MetalMaterial.h"
#include "DielectricMaterial.h"
#include "Random.h"
#include "BVHNode.h"
#include "SingleColorTexture.h"
#include "CheckerTexture.h"
#include "DiffuseLightMaterial.h"
#include "XYRectangle.h"
#include "XZRectangle.h"
#include "YZRectangle.h"
#include "FlipNormals.h"
#include "Box.h"
#include "Translate.h"
#include "RotateY.h"

Hitable** CreateBigHitableList(int& i)
{
	int sphereCount = 500;

	Hitable** list = new Hitable*[sphereCount + 1];

	Material* pMaterial = new LambertianMaterial(new SingleColorTexture(Vec3(0.5f, 0.5f, 0.5f)));
	list[0] = new Sphere(Vec3(0, -1000, 0), 1000, pMaterial);

	i = 1;

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float chooseMtrl = GetRandom0To1();
			Vec3 center(a + 0.9f * GetRandom0To1(), 0.2f, b + 0.9f * GetRandom0To1());
			if ((center - Vec3(4, 0.2f, 0)).GetLength() > 0.9f)
			{
				if (chooseMtrl < 0.8f)
				{
					Vec3 albedo(GetRandom0To1() * GetRandom0To1(), GetRandom0To1() * GetRandom0To1(), GetRandom0To1() * GetRandom0To1());
					SingleColorTexture* pTexture = new SingleColorTexture(albedo);
					pMaterial = new LambertianMaterial(pTexture);
				}
				else if (chooseMtrl < 0.95f)
				{
					Vec3 albedo(0.5f * (1.0f + GetRandom0To1()), 0.5f * (1.0f + GetRandom0To1()), 0.5f * (1.0f + GetRandom0To1()));
					SingleColorTexture* pTexture = new SingleColorTexture(albedo);
					pMaterial = new MetalMaterial(pTexture, 0.5f * GetRandom0To1());
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
	
	pMaterial = new LambertianMaterial(new SingleColorTexture(Vec3(0.4f, 0.2f, 0.1f)));
	list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0f, pMaterial);
	
	pMaterial = new MetalMaterial(new SingleColorTexture(Vec3(0.7f, 0.6f, 0.5f)), 0);
	list[i++] = new Sphere(Vec3(4, 1, 0), 1.0f, pMaterial);

	return list;
}

Hitable** CreateSmallHitableList(int & i)
{
	Hitable** list = new Hitable*[100];

	i = 0;

	Material* pMaterial = new LambertianMaterial(new CheckerTexture(new SingleColorTexture(Vec3(0.2f, 0.1f, 0.2f)), new SingleColorTexture(Vec3(0.9f, 0.9f, 0.9f))));
	list[i++] = new Sphere(Vec3(0, -1000, 0), 1000, pMaterial);

	list[i++] = new Sphere(Vec3(0, 1, 0), 1.0f, new DielectricMaterial(1.5f));

	pMaterial = new LambertianMaterial(new SingleColorTexture(Vec3(0.4f, 0.2f, 0.1f)));
	list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0f, pMaterial);

	pMaterial = new MetalMaterial(new SingleColorTexture(Vec3(0.7f, 0.6f, 0.5f)), 0);
	list[i++] = new Sphere(Vec3(4, 1, 0), 1.0f, pMaterial);

	pMaterial = new LambertianMaterial(new SingleColorTexture(Vec3(0.4f, 0.2f, 0.8f)));
	list[i++] = new MovingSphere(Vec3(6, 1, 0), Vec3(5, 0.5f, 2.5f), 0, 0.1f, 0.2f, pMaterial);

	pMaterial = new DiffuseLightMaterial(new SingleColorTexture(Vec3(25.0f, 22.0f, 22.0f)));
	list[i++] = new XYRectangle(-3, 5, 0.5f, 1, 2, pMaterial);

	return list;
}

Hitable** CreateCornellBoxHitableList(int & i)
{
	Hitable** list = new Hitable*[20];

	i = 0;

	Material* red = new LambertianMaterial(new SingleColorTexture(Vec3(0.65f, 0.05f, 0.05f)));
	list[i++] = new YZRectangle(0, 555, 0, 555, 0, red);

	Material* white = new LambertianMaterial(new SingleColorTexture(Vec3(0.73f, 0.73f, 0.73f)));
	list[i++] = new FlipNormals(new XZRectangle(0, 555, 0, 555, 555, white));
	list[i++] = new XZRectangle(0, 555, 0, 555, 0, white);
	list[i++] = new FlipNormals(new XYRectangle(0, 555, 0, 555, 555, white));

	Box* smallBox = new Box(Vec3(0, 0, 0), Vec3(165, 165, 165), white);
	list[i++] = new Translate(new RotateY(smallBox, -18), Vec3(130, 0, 65));
	
	Box* tallerBox = new Box(Vec3(0, 0, 0), Vec3(165, 330, 165), white);
	list[i++] = new Translate(new RotateY(tallerBox, 15), Vec3(265, 0, 295));

	Material* green = new LambertianMaterial(new SingleColorTexture(Vec3(0.12f, 0.45f, 0.15f)));
	list[i++] = new FlipNormals(new YZRectangle(0, 555, 0, 555, 555, green));

	Material* light = new DiffuseLightMaterial(new SingleColorTexture(Vec3(15, 15, 15)));
	list[i++] = new XZRectangle(213, 343, 227, 332, 554, light);

	return list;
}

Hitable** CreateSampleHitableList(int & i)
{
	Hitable** list = new Hitable*[50];

	i = 0;

	Material* floorMtrl = new LambertianMaterial(new SingleColorTexture(Vec3(0.65f, 0.05f, 0.05f)));
	list[i++] = new YZRectangle(0, 555, 0, 555, 0, floorMtrl);

	Material* white = new LambertianMaterial(new SingleColorTexture(Vec3(0.73f, 0.73f, 0.73f)));
	list[i++] = new FlipNormals(new XZRectangle(0, 555, 0, 555, 555, white));
	list[i++] = new XZRectangle(0, 555, 0, 555, 0, white);
	list[i++] = new FlipNormals(new XYRectangle(0, 555, 0, 555, 555, white));

	Box* smallBox = new Box(Vec3(0, 0, 0), Vec3(165, 165, 165), white);
	list[i++] = new Translate(new RotateY(smallBox, -18), Vec3(130, 0, 65));

	Box* tallerBox = new Box(Vec3(0, 0, 0), Vec3(165, 330, 165), white);
	list[i++] = new Translate(new RotateY(tallerBox, 15), Vec3(265, 0, 295));

	Material* green = new LambertianMaterial(new SingleColorTexture(Vec3(0.12f, 0.45f, 0.15f)));
	list[i++] = new FlipNormals(new YZRectangle(0, 555, 0, 555, 555, green));

	Material* light = new DiffuseLightMaterial(new SingleColorTexture(Vec3(15, 15, 15)));
	list[i++] = new XZRectangle(213, 343, 227, 332, 554, light);

	return list;
}

Hitable* CreateScene(float shutterOpenTime, float shutterCloseTime)
{
	int count;
	
	//Hitable** list = CreateSmallHitableList(count);
	//Hitable** list = CreateBigHitableList(count);
	Hitable** list = CreateCornellBoxHitableList(count);

	//return new HitableList(list, count);
	return new BVHNode(list, count, shutterOpenTime, shutterCloseTime);
}

Vec3 GetBackgroundColor(const Ray& r, int bgType)
{
	switch (bgType)
	{
	case 0: // day light
	{
		Vec3 unitDirection = ConvertToUnitVector(r.direction);
		float t = 0.5f * (unitDirection.Y() + 1);
		return (1.0f - t) * Vec3(1, 1, 1) + t * Vec3(0.5f, 0.7f, 1);
	}
	case 1:  // evening
	{
		Vec3 unitDirection = ConvertToUnitVector(r.direction);
		float t = 0.5f * (unitDirection.Y() + 1);
		return (1.0f - t) * Vec3(0.2f, 0.2f, 0.2f) + t * Vec3(0.05f, 0.15f, 0.2f);
	}
	case 2:
	default:
		return Vec3(0, 0, 0);
	}
}