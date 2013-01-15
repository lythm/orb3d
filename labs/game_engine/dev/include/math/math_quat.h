#ifndef __MATH_QUAT_H__
#define __MATH_QUAT_H__
#pragma once

#ifndef __MATH_TYPES_H__
#include <math/math_types.h>
#endif

namespace math
{
	class Matrix44;
	class Vector3;
	class Quat
	{
	public:
		Quat(void);
		Quat(Real _x, Real _y, Real _z, Real _w);

		~Quat(void);


		Real				Length() const;
		void				MakeIdentity();
		bool				IsIdentity() const;
		void				Conjugate();
		void				Invert();
		void				Normalize();

		const Quat&			operator+=(const Quat& rhs);
		const Quat&			operator-=(const Quat& rhs);
		const Quat&			operator*=(const Quat& rhs);
		const Quat&			operator*=(Real s);
		const Quat&			operator/=(Real s);

		Quat				operator+() const;
		Quat				operator-() const;


		Real	x;
		Real	y;
		Real	z;
		Real	w;

	};

	inline
		Quat Quat::operator+() const
	{
		return *this;
	}
	inline
		Quat Quat::operator-() const
	{
		return Quat(-x, -y, -z, -w);
	}
	inline
		void Quat::Conjugate()
	{
		x = -x;
		y = -y;
		z = -z;
		w = w;
	}
	inline
		void Quat::MakeIdentity()
	{
		x = y = z = 0;
		w = 1;
	}
	inline
		bool Quat::IsIdentity() const
	{
		return x == 0 && y == 0 && z == 0 && w == 1;
	}

	inline
		Real Quat::Length() const
	{
		return sqrt(x * x + y * y + z * z + w * w);

	}
	inline
		const Quat& Quat::operator+=(const Quat& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}
	inline
		const Quat& Quat::operator-=(const Quat& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}
	inline
		const Quat& Quat::operator*=(Real s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}

	inline
		const Quat& Quat::operator/=(Real s)
	{
		x /= s;
		y /= s;
		z /= s;
		w /= s;
		return *this;
	}

	inline
		Quat operator+(const Quat& l, const Quat& r)
	{
		return Quat(l.x + r.x , l.y + r.y , l.z + r.z, l.w + r.w);
	}
	inline
		Quat operator-(const Quat& l, const Quat& r)
	{
		return Quat(l.x - r.x , l.y - r.y , l.z - r.z, l.w - r.w);
	}
	inline 
		Quat operator*(const Quat& l, Real s)
	{
		return Quat(l.x * s, l.y * s, l.z * s, l.w * s);
	}
	inline 
		Quat operator*(Real s, const Quat& l)
	{
		return l * s;
	}
	inline 
		Quat operator*(const Quat& l, const Quat& r)
	{
		Quat ret = l;
		ret *= r;
		return ret;
	}
	inline
		bool operator==(const Quat& l, const Quat& r)
	{
		return l.x == r.x && l.y == r.y && l.z == r.z && l.w == r.w;
	}
	inline 
		bool operator!=(const Quat& l, const Quat& r)
	{
		return !(l == r);
	}

	inline
		Quat::Quat(void)
	{
		x = y = z = w = 0;
	}
	inline
		Quat::Quat(Real _x, Real _y, Real _z, Real _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	inline
		Quat::~Quat(void)
	{
	}
}



#ifdef _D3DX9_IMPL_
#include <math/details/d3d9x/math_quat.inl>
#endif

#ifdef _XNAMATH_IMPL_
#include <math/details/xnamath/math_quat.inl>
#endif

#endif