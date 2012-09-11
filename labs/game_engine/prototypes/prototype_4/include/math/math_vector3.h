#ifndef __MATH_VECTOR3_H__
#define __MATH_VECTOR3_H__
#pragma once

#ifndef __MATH_TYPES_H__
#include <math/math_types.h>
#endif

namespace math
{
	class Vector3
	{
	public:
		Vector3(void);
		Vector3(Real _x, Real _y, Real _z);
		~Vector3(void);

		const Vector3&		operator+=(const Vector3& r);
		const Vector3&		operator-=(const Vector3& r);
		const Vector3&		operator*=(Real s);

		Vector3				operator-() const;
		Vector3				operator+() const;

		Real				Length() const;
		void				Normalize();

		Real				operator[](unsigned int ind) const;
		Real&				operator[](unsigned int ind);


		union
		{
			struct
			{
				Real			x;
				Real			y;
				Real			z;
			};
			Real				v[3];
		};
	};


	inline
		Vector3 Vector3::operator+() const
	{
		return *this;
	}
	inline
		Vector3 Vector3::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	inline
		Real Vector3::Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}
	inline
		const Vector3& Vector3::operator*=(Real s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	inline
		const Vector3& Vector3::operator+=(const Vector3& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;
		return *this;
	}
	inline
		const Vector3& Vector3::operator-=(const Vector3& r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;
		return *this;
	}
	inline
		Real Vector3::operator[](unsigned int ind) const
	{
		return v[ind];
	}
	inline
		Real& Vector3::operator[](unsigned int ind)
	{
		return v[ind];
	}
	inline
		Vector3 operator+(const Vector3& l, const Vector3& r)
	{
		return Vector3(l.x + r.x, l.y + r.y, l.z + r.z);
	}
	inline
		Vector3 operator-(const Vector3& l, const Vector3& r)
	{
		return Vector3(l.x - r.x, l.y - r.y, l.z - r.z);
	}
	inline
		Vector3 operator*(const Vector3& l, Real r)
	{
		return Vector3(l.x * r, l.y * r, l.z * r);
	}
	inline
		Vector3 operator*(Real l, const Vector3& r)
	{
		return Vector3(l * r.x, l * r.y, l* r.z);
	}

	inline
		bool operator==(const Vector3& lhs, const Vector3& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}
	inline
		bool operator!=(const Vector3& lhs, const Vector3& rhs)
	{
		return !(lhs == rhs);
	}

	inline
		Vector3::Vector3(void)
	{
		x = y = z = 0;
	}
	inline
		Vector3::Vector3(Real _x, Real _y, Real _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	inline
		Vector3::~Vector3(void)
	{
	}
}

#ifdef _D3DX9_IMPL_
#include <math/details/d3d9x/math_vector3.inl>
#endif

#ifdef _XNAMATH_IMPL_
#include <math/details/xnamath/math_vector3.inl>
#endif


#endif

