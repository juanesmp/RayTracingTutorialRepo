#pragma once
#include "Sphere.h"
#include "MovingSphere.h"
#include "HitableList.h"
#include "LambertianMaterial.h"
#include "MetalMaterial.h"
#include "DielectricMaterial.h"
#include "Random.h"
#include "BVHNode.h"

Hitable** CreateBigHitableList(int& i)
{
	int sphereCount = 500;

	Hitable** list = new Hitable*[sphereCount + 1];
	list[0] = new Sphere(Vec3(0, -1000, 0), 1000, new LambertianMaterial(Vec3(0.5f, 0.5f, 0.5f)));

	i = 1;

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float chooseMtrl = GetRandom0To1();
			Vec3 center(a + 0.9f * GetRandom0To1(), 0.2f, b + 0.9f * GetRandom0To1());
			if ((center - Vec3(4, 0.2f, 0)).GetLength() > 0.9f)
			{
				Material* pMaterial;
				if (chooseMtrl < 0.8f)
				{
					Vec3 albedo(GetRandom0To1() * GetRandom0To1(), GetRandom0To1() * GetRandom0To1(), GetRandom0To1() * GetRandom0To1());
					pMaterial = new LambertianMaterial(albedo);
				}
				else if (chooseMtrl < 0.95f)
				{
					Vec3 albedo(0.5f * (1.0f + GetRandom0To1()), 0.5f * (1.0f + GetRandom0To1()), 0.5f * (1.0f + GetRandom0To1()));
					pMaterial = new MetalMaterial(albedo, 0.5f * GetRandom0To1());
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

	return list;
}

Hitable** CreateSmallHitableList(int & i)
{
	Hitable** list = new Hitable*[100];

	i = 0;

	list[i++] = new Sphere(Vec3(0, -1000, 0), 1000, new LambertianMaterial(Vec3(0.5f, 0.5f, 0.5f)));

	list[i++] = new Sphere(Vec3(0, 1, 0), 1.0f, new DielectricMaterial(1.5f));
	list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0f, new LambertianMaterial(Vec3(0.4f, 0.2f, 0.1f)));
	list[i++] = new Sphere(Vec3(4, 1, 0), 1.0f, new MetalMaterial(Vec3(0.7f, 0.6f, 0.5f), 0));

	list[i++] = new MovingSphere(Vec3(6, 1, 0), Vec3(5, 0.5f, 2.5f), 0, 0.1f, 0.2f, new LambertianMaterial(Vec3(0.4f, 0.2f, 0.8f)));

	return list;
}

Hitable* CreateScene(float shutterOpenTime, float shutterCloseTime)
{
	int count;
	
	//Hitable** list = CreateSmallHitableList(count);
	Hitable** list = CreateBigHitableList(count);
	
	//return new HitableList(list, count);
	return new BVHNode(list, count, shutterOpenTime, shutterCloseTime);
}