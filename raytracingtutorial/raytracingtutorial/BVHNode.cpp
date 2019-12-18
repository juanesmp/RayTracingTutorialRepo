#include "pch.h"
#include <stdlib.h>
#include "BVHNode.h"

int CompareBoxes(const void * a, const void * b)
{
	Hitable * hitableA = *(Hitable**)a;
	Hitable * hitableB = *(Hitable**)b;

	AABB boxA, boxB;
	hitableA->GetBoundingBoxAtTime(0, 0, boxA);
	hitableB->GetBoundingBoxAtTime(0, 0, boxB);

	if (boxA.GetMin().X() < boxB.GetMin().X())
		return -1;
	else
		return 1;
}

BVHNode::BVHNode(Hitable ** hitableList, int hitableCount, float startTime, float endTime)
{
	qsort(hitableList, hitableCount, sizeof(Hitable*), CompareBoxes);

	switch (hitableCount)
	{
	case 1:
		left = right = hitableList[0];
		break;
	case 2:
		left = hitableList[0];
		right = hitableList[1];
		break;
	default:
		left = new BVHNode(hitableList, hitableCount / 2, startTime, endTime);
		right = new BVHNode(hitableList + hitableCount / 2, hitableCount - (hitableCount / 2), startTime, endTime);
		break;
	}

	AABB boxLeft, boxRight;
	left->GetBoundingBoxAtTime(startTime, endTime, boxLeft);
	right->GetBoundingBoxAtTime(startTime, endTime, boxRight);

	aabb = CombineAABBs(boxLeft, boxRight);
}

bool BVHNode::DoesRayHit(const Ray & ray, float minLength, float maxLength, HitRecord & hit) const
{
	bool didHit = false;

	if (aabb.DoesRayHit(ray, minLength, maxLength))
	{
		HitRecord leftHit, rightHit;

		bool didHitLeft = left->DoesRayHit(ray, minLength, maxLength, leftHit);
		bool didHitRight = right->DoesRayHit(ray, minLength, maxLength, rightHit);
		
		if (didHitLeft && didHitRight)
		{
			hit = (leftHit.length < rightHit.length) ? leftHit : rightHit;
			didHit = true;
		}
		else if (didHitLeft)
		{
			hit = leftHit;
			didHit = true;
		}
		else if (didHitRight)
		{
			hit = rightHit;
			didHit = true;
		}
	}

	return didHit;
}

bool BVHNode::GetBoundingBoxAtTime(float startTime, float endTime, AABB & box) const
{
	box = aabb;
	return true;
}
