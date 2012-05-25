#ifndef __MATH_SPHERE_H__
#define __MATH_SPHERE_H__
#pragma once

#ifndef __MATH_VECTOR3_H__
#include <math/math_vector3.h>
#endif

namespace math
{
	class Sphere
	{
	public:
		Sphere(const Vector3& c, Real r);
		Sphere();
		~Sphere(void);


		Vector3				center;
		Real				radius;
	};

	inline
		Sphere::Sphere(const Vector3& c, Real r) : center(c), radius(r)
	{

	}
	inline
		Sphere::Sphere(void) :center(0, 0, 0), radius(0)
	{
	}
	inline
		Sphere::~Sphere(void)
	{
	}
}
#endif