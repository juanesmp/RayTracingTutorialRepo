#pragma once

class Vec3
{
public:
	Vec3();
	Vec3(float e0, float e1, float e2);

	inline float X() const { return e[0]; }
	inline float Y() const { return e[1]; }
	inline float Z() const { return e[2]; }
	
	inline float R() const { return e[0]; }
	inline float G() const { return e[1]; }
	inline float B() const { return e[2]; }

	float e[3];
};
