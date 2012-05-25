#pragma once

#include <orbmathtypes.h>
#include <vector3.h>

namespace math
{
	class Ray
	{
	public:
		Ray(void);
		Ray(const vector3& o, const vector3& d);
		~Ray(void);

		vector3			getPoint(real t) const;

		vector3			ori;
		vector3			dir;
	};

	inline
		Ray::Ray(void)
	{
	}
	inline
		Ray::Ray(const vector3& o, const vector3& d)
	{
		ori = o;
		dir = d;
	}
	inline
		Ray::~Ray(void)
	{
	}

	inline
	vector3	Ray::getPoint(real t) const
	{
		return ori + t * dir;
	}

}