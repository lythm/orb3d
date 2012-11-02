#ifndef __MATH_VECTOR4_H__
#define __MATH_VECTOR4_H__
#pragma once

#ifndef __MATH_TYPES_H__
#include <math/math_types.h>
#endif

namespace math
{
	class Vector4
	{
	public:
		Vector4(void);
		Vector4(Real _x, Real _y, Real _z, Real _w);
		~Vector4(void);


		const Vector4&		operator+=(const Vector4& r);
		const Vector4&		operator-=(const Vector4& r);
		const Vector4&		operator*=(Real s);

		Vector4				operator+() const;
		Vector4				operator-() const; 

		Real				Length() const;
		void				Normalize();

		union
		{
			struct
			{
				Real			x;
				Real			y;
				Real			z;
				Real			w;
			};
			Real				v[4];
		};
	};

	inline
		Vector4 Vector4::operator+() const
	{
		return *this;
	}

	inline
		Vector4 Vector4::operator-() const
	{
		return Vector4(-x, -y, -z, -w);
	}
	inline
		Real Vector4::Length() const
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}
	inline
		const Vector4& Vector4::operator*=(Real s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}
	inline
		const Vector4& Vector4::operator+=(const Vector4& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;
		w += r.w;
		return *this;
	}
	inline
		const Vector4& Vector4::operator-=(const Vector4& r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;
		w -= r.w;
		return *this;
	}
	inline
		Vector4 operator+(const Vector4& l, const Vector4& r)
	{
		return Vector4(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
	}
	inline
		Vector4 operator-(const Vector4& l, const Vector4& r)
	{
		return Vector4(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
	}
	inline
		Vector4 operator*(const Vector4& l, Real r)
	{
		return Vector4(l.x * r, l.y * r, l.z * r, l.w * r);
	}
	inline
		Vector4 operator*(Real l, const Vector4& r)
	{
		return Vector4(l * r.x, l * r.y, l * r.z, l * r.w);
	}

	inline
		bool operator==(const Vector4& lhs, const Vector4& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
	}
	inline
		bool operator!=(const Vector4& lhs, const Vector4& rhs)
	{
		return !(lhs == rhs);
	}

	inline
		Vector4::Vector4(void)
	{
		x = y = z = w = 0;
	}

	inline
		Vector4::Vector4(Real _x, Real _y, Real _z, Real _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	inline
		Vector4::~Vector4(void)
	{
	}
}


#ifdef _D3DX9_IMPL_
#include <math/details/d3d9x/math_vector4.inl>
#endif

#ifdef _XNAMATH_IMPL_
#include <math/details/xnamath/math_vector4.inl>
#endif


#endif