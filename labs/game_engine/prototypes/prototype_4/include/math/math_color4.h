#ifndef __MATH_COLOR4_H__
#define __MATH_COLOR4_H__
#pragma once

#ifndef __MATH_TYPES_H__
#include <math/math_types.h>
#endif

namespace math
{
	class Color4
	{
	public:
		Color4(void);
		Color4(Real _r, Real _g, Real _b, Real _a);
		Color4(unsigned long clr);
		~Color4(void);

		unsigned long	AsULong() const;

		Real			Grey() const;
		const Color4&	operator+=(const Color4& rhs);
		const Color4&	operator-=(const Color4& rhs);
		const Color4&	operator*=(const Color4& rhs);
		const Color4&	operator*=(Real s);
		void			Clamp(const Color4& minval, const Color4& maxval);
		void			Negative();

		union
		{
			struct
			{
				Real			r;
				Real			g;
				Real			b;
				Real			a;
			};
			float				v[4];
		};
	};


	inline
		unsigned long	Color4::AsULong() const
	{
		return (unsigned long(r * 255) << 16) | 
			(unsigned long(g * 255) << 8) |
			(unsigned long(b * 255) ) |
			(unsigned long(a * 255) << 24);
	}

	inline
		void Color4::Negative()
	{
		r = 1 - r;
		g = 1 - g;
		b = 1 - b;
		a = a;
	}
	inline
		void Color4::Clamp(const Color4& minval, const Color4& maxval)
	{
		if(r < minval.r)	r = minval.r;
		if(r > maxval.r)	r = maxval.r;

		if(g < minval.g)	g = minval.g;
		if(g > maxval.g)	g = maxval.g;

		if(b < minval.b)	b = minval.b;
		if(b > maxval.b)	b = maxval.b;

		if(a < minval.a)	a = minval.a;
		if(a > maxval.a)	a = maxval.a;

	}
	inline
		Real Color4::Grey() const
	{
		return r * 0.2125f + g * 0.7154f + b * 0.0721f;
	}
	inline
		const Color4& Color4::operator*=(Real s)
	{
		r *= s;
		g *= s;
		b *= s;
		a *= s;
		return *this;
	}
	inline
		const Color4&	Color4::operator+=(const Color4& rhs)
	{
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		a += rhs.a;
		return *this;
	}
	inline
		const Color4&	Color4::operator-=(const Color4& rhs)
	{
		r -= rhs.r;
		g -= rhs.g;
		b -= rhs.b;
		a -= rhs.a;
		return *this;
	}
	inline
		const Color4&	Color4::operator*=(const Color4& rhs)
	{
		r *= rhs.r;
		g *= rhs.g;
		b *= rhs.b;
		a *= rhs.a;
		return *this;
	}

	inline
		Color4 operator+(const Color4& lhs, const Color4& rhs)
	{
		return Color4(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b, lhs.a + rhs.a);
	}
	inline 
		Color4 operator-(const Color4& lhs, const Color4& rhs)
	{
		return Color4(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b, lhs.a - rhs.a);
	}
	inline 
		Color4 operator*(const Color4& lhs, const Color4& rhs)
	{
		return Color4(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b, lhs.a * rhs.a);
	}
	inline 
		Color4 operator*(const Color4& clr, Real s)
	{
		return Color4(clr.r * s, clr.g * s, clr.b * s, clr.a * s);
	}
	inline 
		Color4 operator*(Real s, const Color4& clr)
	{
		return Color4(clr.r * s, clr.g * s, clr.b * s, clr.a * s);
	}

	inline
		Color4::Color4(void)
	{
		r = g = b = a = 0;
	}
	inline
		Color4::Color4(Real _r, Real _g, Real _b, Real _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
	inline
		Color4::Color4(unsigned long clr)
	{
		a = Real((clr & 0xff000000) >> 24) / Real(255);
		r = Real((clr & 0x00ff0000) >> 16) / Real(255);
		g = Real((clr & 0x0000ff00) >> 8) / Real(255);
		b = Real((clr & 0x000000ff)) / Real(255);
	}
	inline
		Color4::~Color4(void)
	{
	}
}
#endif