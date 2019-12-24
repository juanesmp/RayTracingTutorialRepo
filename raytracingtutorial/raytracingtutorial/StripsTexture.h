#pragma once
#include "Texture.h"

class StripsTexture : public Texture
{
public:
	StripsTexture() {}
	StripsTexture(Texture* odd, Texture* even) : pOddTexture(odd), pEvenTexture(even) {}

	virtual Vec3 Sample(float u, float v, const Vec3 & point) const override;

private:
	Texture* pOddTexture;
	Texture* pEvenTexture;
};

