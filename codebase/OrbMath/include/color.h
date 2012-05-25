#pragma once

#include <orbmathtypes.h>
#include <alg.h>
namespace math
{
	class color
	{
	public:
		color(void);
		color(real _r, real _g, real _b, real _a);
		color(dword clr);
		~color(void);

		void clamp(real min, real max);

		const color& operator +=(const color& rhw);
		const color& operator *=(const color& rhw);
		const color& operator *=(real rhw);
		const color& operator /=(real rhw);

		dword	asARGB() const;
		dword	asRGBA() const;
		
		real	r;
		real	g;
		real	b;
		real	a;
	};

	inline
		color::color(void)
	{
		a = r = g = b = real(0);
	}

	inline
		color::color(real _r, real _g, real _b, real _a)
	{
		a = _a;
		r = _r;
		g = _g;
		b = _b;
	}
	inline
		color::color(dword clr)
	{
		a = (real)((clr >> 24)& 0x000000ff) / real(255);
		r = (real)((clr >> 16)& 0x000000ff) / real(255);
		g = (real)((clr >> 8)& 0x000000ff) / real(255);
		b = (real)((clr)& 0x000000ff) / real(255);
	}
	inline
		color::~color(void)
	{
	}

	inline
		void color::clamp(real min, real max)
	{
		math::clamp(r, min, max);
		math::clamp(g, min, max);
		math::clamp(b, min, max);
		math::clamp(a, min, max);
	}
	inline
		const color& color::operator +=(const color& rhw)
	{
		r += rhw.r;
		g += rhw.g;
		b += rhw.b;
		a += rhw.a;
		return *this;
	}
	inline
		const color& color::operator *=(const color& rhw)
	{
		r *= rhw.r;
		g *= rhw.g;
		b *= rhw.b;
		a *= rhw.a;
		return *this;
	}
	inline
		const color& color::operator *=(real rhw)
	{
		r *= rhw;
		g *= rhw;
		b *= rhw;
		a *= rhw;

		return *this;
	}
	inline
		const color& color::operator /=(real rhw)
	{
		r /= rhw;
		g /= rhw;
		b /= rhw;
		a /= rhw;
		return *this;
	}

	inline
		dword	color::asARGB() const
	{
		dword c = 0;
		c = (dword)(((byte)(a * 255) << 24) 
			| ((byte)(r * 255) << 16)
			| ((byte)(g * 255) << 8)
			| ((byte)(b * 255)));
		return c;
	}
	inline
		dword color::asRGBA() const
	{
		dword c = 0;
		c = (dword)(((byte)(r * 255) << 24) 
			| ((byte)(g * 255) << 16)
			| ((byte)(b * 255) << 8)
			| ((byte)(a * 255)));
		return c;
	}
}