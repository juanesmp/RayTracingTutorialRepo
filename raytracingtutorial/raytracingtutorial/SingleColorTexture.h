#pragma once
#include "Texture.h"

class SingleColorTexture : public Texture
{
public:
	SingleColorTexture() {}
	SingleColorTexture(Vec3 _color) : color(_color) {}

	virtual Vec3 Sample(float u, float v, const Vec3 & point) const override { return color; }

private:
	Vec3 color;
};
