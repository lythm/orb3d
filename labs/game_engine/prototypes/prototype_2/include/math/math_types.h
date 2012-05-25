#ifndef __MATH_TYPES_H__
#define __MATH_TYPES_H__
#pragma once

//#include <math>
#include <limits>

#ifdef PI
#undef PI
#endif

#ifdef TWO_PI
#undef TWO_PI
#endif


typedef float				Real;

namespace math
{
	const Real PI					= Real(3.1415926);
	const Real TWO_PI				= PI * 2;
	const Real HALF_PI				= PI / Real(2.0f);

	const Real REAL_MAX				= std::numeric_limits<Real>::max();
	const Real REAL_MIN				= std::numeric_limits<Real>::min();
	const Real REAL_INFINITY		= std::numeric_limits<Real>::infinity();
	const Real REAL_EPSILON			= std::numeric_limits<Real>::epsilon();
}
#endif
