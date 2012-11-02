#ifndef __MATH_VECTOR2_H__
#define __MATH_VECTOR2_H__
#pragma once

#ifndef __MATH_TYPES_H__
#include <math/math_types.h>
#endif

namespace math
{
	class Vector2
	{
	public:
		Vector2(void);
		Vector2(Real _x, Real _y);

		~Vector2(void);

		const Vector2&		operator+=(const Vector2& r);
		const Vector2&		operator-=(const Vector2& r);
		const Vector2&		operator*=(Real s);

		Vector2				operator+() const;
		Vector2				operator-() const;

		Real				Length() const;
		void				Normalize();

		union
		{
			struct
			{
				Real		x;
				Real		y;
			};
			Real			v[2];
		};
	};

	inline
		Vector2::Vector2(void)
	{
		x = 0;
		y = 0;
	}
	inline
		Vector2::Vector2(Real _x, Real _y)
	{
		x = _x;
		y = _y;
	}
	inline
		Vector2::~Vector2(void)
	{
	}

	inline
		Vector2 Vector2::operator+() const
	{
		return *this;
	}
	inline
		Vector2 Vector2::operator-() const
	{
		return Vector2(-x, -y);;
	}
	inline
		Real Vector2::Length() const
	{
		return sqrtf(x * x + y * y);
	}
	inline
		const Vector2& Vector2::operator*=(Real s)
	{
		x *= s;
		y *= s;
		return *this;
	}
	inline
		const Vector2& Vector2::operator+=(const Vector2& r)
	{
		x += r.x;
		y += r.y;
		return *this;
	}
	inline
		const Vector2& Vector2::operator-=(const Vector2& r)
	{
		x -= r.x;
		y -= r.y;
		return *this;
	}
	inline
		Vector2 operator+(const Vector2& l, const Vector2& r)
	{
		return Vector2(l.x + r.x, l.y + r.y);
	}
	inline
		Vector2 operator-(const Vector2& l, const Vector2& r)
	{
		return Vector2(l.x - r.x, l.y - r.y);
	}
	inline
		Vector2 operator*(const Vector2& l, Real r)
	{
		return Vector2(l.x * r, l.y * r);
	}
	inline
		Vector2 operator*(Real l, const Vector2& r)
	{
		return Vector2(l * r.x, l * r.y);
	}

	inline
		bool operator==(const Vector2& lhs, const Vector2& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
	inline
		bool operator!=(const Vector2& lhs, const Vector2& rhs)
	{
		return !(lhs == rhs);
	}
}

#ifdef _D3DX9_IMPL_
#include <math/details/d3d9x/math_vector2.inl>
#endif

#ifdef _XNAMATH_IMPL_
#include <math/details/xnamath/math_vector2.inl>
#endif

#endif
