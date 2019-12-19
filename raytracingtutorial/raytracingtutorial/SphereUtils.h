#pragma once

#include "Hitable.h"

void GetSpehereTextureUV(const Vec3 & point, float & u, float & v);
AABB GetSphereBoundingBox(Vec3 center, float radius);