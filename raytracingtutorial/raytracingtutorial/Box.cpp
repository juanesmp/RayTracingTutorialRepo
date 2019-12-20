#include "pch.h"
#include "Box.h"
#include "XYRectangle.h"
#include "XZRectangle.h"
#include "YZRectangle.h"
#include "FlipNormals.h"
#include "HitableList.h"
#include "AABB.h"

Box::Box(const Vec3 & _min, const Vec3 & _max, Material * pMaterial)
{
	min = _min;
	max = _max;

	Hitable ** list = new Hitable*[6];
	
	list[0] = new XYRectangle(min.X(), max.X(), min.Y(), max.Y(), max.Z(), pMaterial);
	list[1] = new FlipNormals(new XYRectangle(min.X(), max.X(), min.Y(), max.Y(), min.Z(), pMaterial));
	
	list[2] = new XZRectangle(min.X(), max.X(), min.Z(), max.Z(), max.Y(), pMaterial);
	list[3] = new FlipNormals(new XZRectangle(min.X(), max.X(), min.Z(), max.Z(), min.Y(), pMaterial));
	
	list[4] = new YZRectangle(min.Y(), max.Y(), min.Z(), max.Z(), max.X(), pMaterial);
	list[5] = new FlipNormals(new YZRectangle(min.Y(), max.Y(), min.Z(), max.Z(), min.X(), pMaterial));

	facesList = new HitableList(list, 6);
}

bool Box::DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const
{
	return facesList->DoesRayHit(ray, minLength, maxLength, hit);
}

bool Box::GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const
{
	box = AABB(min, max);
	return true;
}
