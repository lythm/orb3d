#ifndef __MATH_PLANE_H__
#define __MATH_PLANE_H__
#pragma once

#ifndef __MATH_TYPES_H__
#include <math/math_types.h>
#endif

#ifndef __MATH_VECTOR3_H__
#include <math/math_vector3.h>
#endif

namespace math
{
	class Plane
	{
	public:
		Plane(void);
		Plane(Real _a, Real _b, Real _c, Real _d);
		Plane(const Vector3& _normal, Real _dist);
		Plane(const Vector3& n, const Vector3& p);
		Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3);
		~Plane(void);

		Plane				operator+() const;
		Plane				operator-() const;

		const Plane&		operator*=(Real s);
		const Plane&		operator/=(Real s);

		void Normalize();

		union
		{
			struct
			{
				Real a, b, c, d;
			};
			struct
			{	
				Vector3		normal;
				Real		dist;
			};
		};
	};

	inline
		Plane Plane ::operator+() const
	{
		return *this;
	}
	inline
		Plane Plane ::operator-() const
	{
		return Plane(-a, -b, -c, -d);
	}
	inline
		const Plane& Plane::operator*=(Real s)
	{
		a *= s;
		b *= s;
		c *= s;
		d *= s;
		return *this;
	}
	inline
		const Plane& Plane::operator/=(Real s)
	{
		*this *= (Real(1) / s);
		return *this;
	}

	inline
		Plane operator*(Real s, const Plane& p)
	{
		Plane ret = p;
		ret *= s;
		return ret;
	}
	inline
		Plane operator*(const Plane& p, Real s)
	{
		return s * p;
	}

	inline
		Plane operator/(const Plane& p, Real s)
	{
		Plane ret = p;
		ret /= s;
		return ret;
	}

	inline 
		bool operator==(const Plane& lhs, const Plane& rhs)
	{
		return lhs.a == rhs.a && lhs.b == rhs.b && lhs.c == rhs.c && lhs.d == rhs.d;
	}
	inline 
		bool operator!=(const Plane& lhs, const Plane& rhs)
	{
		return !(lhs == rhs);
	}

	inline
		Plane::Plane(void)
	{
		a = b = c = d = 0;
	}
	inline
		Plane::Plane(Real _a, Real _b, Real _c, Real _d)
	{
		a = _a;
		b = _b;
		c = _c;
		d = _d;
	}
	inline
		Plane::Plane(const Vector3& _normal, Real _dist)
	{
		normal	= _normal;
		dist	= _dist;
	}
	inline
		Plane::~Plane(void)
	{
	}
}

#ifdef _D3DX9_IMPL_
#include <math/details/d3d9x/math_plane.inl>
#endif

#ifdef _XNAMATH_IMPL_
#include <math/details/xnamath/math_plane.inl>
#endif


#endif