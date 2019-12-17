#include "pch.h"
#include "Random.h"
#include "Vec3.h"
#include <stdlib.h> 

float GetRandom0To1()
{
	return float(rand()) / float(RAND_MAX + 1);
}

Vec3 GetRandomVec3InUnitSphere()
{
	Vec3 p;
	do
	{
		p = 2.0f * Vec3(GetRandom0To1(), GetRandom0To1(), GetRandom0To1()) - Vec3(1, 1, 1);
	} while (p.GetSquaredLength() >= 1.0f);

	return p;
}

Vec3 GetRandomVec3InUnitDisk()
{
	Vec3 p;
	do
	{
		p = 2.0f * Vec3(GetRandom0To1(), GetRandom0To1(), 0) - Vec3(1, 1, 0);
	} while (Dot(p, p) >= 1.0f);

	return p;
}
