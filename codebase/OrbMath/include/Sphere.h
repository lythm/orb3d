#pragma once

#include <orbmathtypes.h>
#include <vector3.h>

namespace math
{
	class Sphere
	{
	public:
		Sphere(void);
		~Sphere(void);

		Sphere(const vector3& c, real r);

		bool operator==(const Sphere& other);

		vector3				center;
		real				radius;
	};

	inline
		Sphere::Sphere(void)
	{
		radius = real(0);
	}
	inline
		Sphere::Sphere(const vector3& c, real r)
	{
		center = c;
		radius = r;
	}

	inline
		Sphere::~Sphere(void)
	{
	}
}