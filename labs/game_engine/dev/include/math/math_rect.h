#ifndef __MATH_RECT_H__
#define __MATH_RECT_H__
#pragma once

#ifndef __MATH_TYPES_H__
#include <math/math_types.h>
#endif

namespace math
{
	template <typename T>
	class Rect
	{
	public:
		Rect(void)
		{
			left		= 0;
			top			= 0;
			right		= 0;
			bottom		= 0;
		}
		Rect(T l, T t, T r, T b) : left(l), top(t), right(r), bottom(b)	{}

		~Rect(void)	{}


		T			left;
		T			top;
		T			right;
		T			bottom;
	};

	typedef Rect<int>		RectI;
	typedef Rect<Real>		RectR;
}
#endif