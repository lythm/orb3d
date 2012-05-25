#ifndef __MATH_RAY_H__
#define __MATH_RAY_H__
#pragma once

#ifndef __MATH_VECTOR3_H__
#include <math/math_vector3.h>
#endif

namespace math
{
	class Ray
	{
	public:
		Ray(void);
		Ray(const Vector3& ori, const Vector3& dir);
		~Ray(void);


		Vector3			GetPos(Real t) const;
		Real			GetT(const Vector3& pos) const;

		Vector3			o;
		Vector3			d;
	};


	inline
		Vector3	Ray::GetPos(Real t) const
	{
		return o + d * t;
	}
	inline
		Real Ray::GetT(const Vector3& pos) const
	{
		if(d.x != 0)
			return (pos.x - o.x) / d.x;
		if(d.y != 0)
			return (pos.y - o.y) / d.y;
		if(d.z != 0)
			return (pos.z - o.z) / d.z;
		return 0;
	}
	inline
		Ray::Ray(void)
	{
		o = Vector3(0, 0, 0);
		d = Vector3(0, 0, 0);
	}
	inline
		Ray::Ray(const Vector3& ori, const Vector3& dir) : o(ori), d(dir)
	{
	}
	inline
		Ray::~Ray(void)
	{
	}
}
#endif