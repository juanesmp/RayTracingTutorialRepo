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
#include "StripsTexture.h"
#include "DiffuseLightMaterial.h"
#include "XYRectangle.h"
#include "XZRectangle.h"
#include "YZRectangle.h"
#include "FlipNormals.h"
#include "Box.h"
#include "Translate.h"
#include "RotateY.h"
#include "ConstantMedium.h"

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

	pMaterial = new LambertianMaterial(new SingleColorTexture(Vec3(1, 1, 1)));
	Sphere * s = new Sphere(Vec3(3, 1, 2), 1.0f, pMaterial);
	list[i++] = new ConstantMedium(s, 0.5f, new SingleColorTexture(Vec3(1, 1, 1)));

	pMaterial = new LambertianMaterial(new SingleColorTexture(Vec3(0.4f, 0.2f, 0.8f)));
	list[i++] = new MovingSphere(Vec3(6, 1, 0), Vec3(5, 0.5f, 2.5f), 0, 0.1f, 0.2f, pMaterial);

	//pMaterial = new DiffuseLightMaterial(new SingleColorTexture(Vec3(25.0f, 22.0f, 22.0f)));
	//list[i++] = new XYRectangle(-3, 5, 0.5f, 1, 2, pMaterial);

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
	Hitable** list = new Hitable*[500];

	i = 0;

	CheckerTexture* checker = new CheckerTexture(new SingleColorTexture(Vec3(0.8f, 0.5f, 0.5f)), new SingleColorTexture(Vec3(0.9f, 0.9f, 0.9f)));
	Material* floorMtrl = new LambertianMaterial(checker);
	list[i++] = new Sphere(Vec3(0, -1000, 0), 1000, floorMtrl);

	Material* light = new DiffuseLightMaterial(new SingleColorTexture(Vec3(30, 24, 18)));
	//list[i++] = new Sphere(Vec3(3, 2, 2), 0.5f, light);

	for (int j = 0; j < 5; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			int x = -9 + k * 6;
			int z = -14 + j * 8;
			list[i++] = new Sphere(Vec3(float(x), 2.5f, float(z)), 0.5f, light);
		}
	}

	Material* dielectric = new DielectricMaterial(1.5f);
	list[i++] = new Sphere(Vec3(4, 0.5f, 1), 0.5f, dielectric);
	list[i++] = new Sphere(Vec3(2, 0.5f, -3), 0.5f, dielectric);
	list[i++] = new Sphere(Vec3(-8, 0.5f, -4), 0.5f, dielectric);
	list[i++] = new Sphere(Vec3(-5, 0.5f, -8), 0.5f, dielectric);
	Sphere* sp = new Sphere(Vec3(6, 0.5f, 0), 0.5f, dielectric);
	list[i++] = sp;
	list[i++] = new ConstantMedium(sp, 3.1f, new SingleColorTexture(Vec3(0.2f, 0.4f, 0.9f)));

	Box* box = new Box(Vec3(0, 0, 0), Vec3(0.5f, 0.5f, 0.5f), dielectric);
	Vec3 pos = Vec3(4, 0, 2); 
	//list[i++] = new Translate(new RotateY(box, 5.0f), pos);

	Material * greenL = new MetalMaterial(new SingleColorTexture(Vec3(0.35f, 0.95f, 0.95f)), 0.15f);
	box = new Box(Vec3(0, 0, 0), Vec3(1.0f, 2.0f, 2.0f), greenL);
	pos = Vec3(1.5f, 0, 2);
	list[i++] = new Translate(new RotateY(box, 25.0f), pos);

	StripsTexture* redStripsTex = new StripsTexture(new SingleColorTexture(Vec3(0.95f, 0.25f, 0.15f)), new SingleColorTexture(Vec3(0.4f, 0.1f, 0.1f)));
	StripsTexture* greenStripsTex = new StripsTexture(new SingleColorTexture(Vec3(0.12f, 0.95f, 0.25f)), new SingleColorTexture(Vec3(0.12f, 0.4f, 0.15f)));
	StripsTexture* blueStripsTex = new StripsTexture(new SingleColorTexture(Vec3(0.12f, 0.35f, 0.95f)), new SingleColorTexture(Vec3(0.12f, 0.15f, 0.4f)));
	
	Material* redStrips = new MetalMaterial(redStripsTex, 0.04f);
	Material* greenStrips = new MetalMaterial(greenStripsTex, 0.06f);
	Material* blueStrips = new MetalMaterial(blueStripsTex, 0.07f);

	Material* red = new MetalMaterial(new SingleColorTexture(Vec3(0.95f, 0.35f, 0.35f)), 0.04f);
	Material* green = new MetalMaterial(new SingleColorTexture(Vec3(0.22f, 0.95f, 0.25f)), 0.06f);
	Material* blue = new MetalMaterial(new SingleColorTexture(Vec3(0.32f, 0.35f, 0.95f)), 0.07f);

	for (int j = 0; j < 40; j++)
	{
		Material* mtrl;
		switch (j % 6)
		{
		case 0: mtrl = red; break;
		case 1: mtrl = blue; break;
		case 2: mtrl = green; break;
		case 3: mtrl = redStrips; break;
		case 4: mtrl = blueStrips; break;
		default: mtrl = greenStrips; break;
		}

		Box* box = new Box(Vec3(0, 0, 0), Vec3(1.0f + GetRandom0To1() * 4.0f, 1.0f + GetRandom0To1() * 4.0f, 1.0f + GetRandom0To1() * 4.0f), mtrl);
		Vec3 pos = Vec3(-10.f - GetRandom0To1() * 15.0f, -0.5f, -32.0f + GetRandom0To1() * 40.0f);
		//list[i++] = new Translate(new RotateY(box, GetRandom0To1() * 25.0f), pos);
		list[i++] = new Translate(box, pos);
	}

	for (int j = 0; j < 35; j++)
	{
		Material* mtrl;
		switch (j % 6)
		{
		case 0: mtrl = red; break;
		case 1: mtrl = blue; break;
		case 2: mtrl = green; break;
		case 3: mtrl = redStrips; break;
		case 4: mtrl = blueStrips; break;
		default: mtrl = greenStrips; break;
		}

		Box* box = new Box(Vec3(0, 0, 0), Vec3(2.0f + GetRandom0To1() * 6.0f, 2.0f + GetRandom0To1() * 6.0f, 2.0f + GetRandom0To1() * 6.0f), mtrl);
		Vec3 pos = Vec3(+10.f + GetRandom0To1() * 15.0f, -0.5f, -65.0f + GetRandom0To1() * 80.0f);
		//list[i++] = new Translate(new RotateY(box, GetRandom0To1() * 25.0f), pos);
		list[i++] = new Translate(box, pos);
	}

	Material* white = new LambertianMaterial(new SingleColorTexture(Vec3(1, 1, 1)));
	Box * b = new Box(Vec3(-9, 0.5f, -20), Vec3(9, 7, 20), white);
	list[i++] = new ConstantMedium(b, 0.002f, new SingleColorTexture(Vec3(1, 1, 1)));
	b = new Box(Vec3(-18, 0.5f, -30), Vec3(-9, 7, 10), white);
	list[i++] = new ConstantMedium(b, 0.002f, new SingleColorTexture(Vec3(1, 1, 1)));

	return list;
}

Hitable* CreateScene(float shutterOpenTime, float shutterCloseTime)
{
	int count;
	
	//Hitable** list = CreateSmallHitableList(count);
	//Hitable** list = CreateBigHitableList(count);
	//Hitable** list = CreateCornellBoxHitableList(count);
	Hitable** list = CreateSampleHitableList(count);

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
		//return (1.0f - t) * Vec3(0.2f, 0.2f, 0.2f) + t * Vec3(0.125f, 0.15f, 0.3f);
		return (1.0f - t) * Vec3(0.15f, 0.15f, 0.15f) + t * Vec3(0.075f, 0.1f, 0.15f);
	}
	case 2:
	default:
		return Vec3(0, 0, 0);
	}
}