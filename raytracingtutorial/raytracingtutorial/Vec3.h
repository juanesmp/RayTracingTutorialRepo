#pragma once

#include <math.h>

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

	inline Vec3& operator+=(const Vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	inline Vec3& operator-=(const Vec3& v)
	{
		e[0] -= v.e[0];
		e[1] -= v.e[1];
		e[2] -= v.e[2];
		return *this;
	}

	inline Vec3& operator*=(const float t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	inline Vec3& operator/=(const float t)
	{
		e[0] /= t;
		e[1] /= t;
		e[2] /= t;
		return *this;
	}

	inline float GetLength() const
	{
		return float(sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]));
	}

	inline float GetSquaredLength() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	float e[3];
};

inline Vec3 operator+(const Vec3 & v1, const Vec3& v2)
{
	return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3 operator-(const Vec3 & v1, const Vec3& v2)
{
	return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(const Vec3 & v1, const Vec3 & v2)
{
	return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3 operator*(const Vec3 & v, float t)
{
	return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator*(float t, const Vec3 & v)
{
	return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator/(const Vec3 & v, float t)
{
	return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline Vec3 ConvertToUnitVector(Vec3 v)
{
	return v / v.GetLength();
}

inline float Dot(const Vec3 & v1, const Vec3& v2)
{
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}