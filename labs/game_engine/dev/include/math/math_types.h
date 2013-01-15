#ifndef __MATH_TYPES_H__
#define __MATH_TYPES_H__
#pragma once

//#include <math>
#include <limits>

#ifdef MATH_PI
#undef MATH_PI
#endif



typedef float				Real;

namespace math
{
	const Real MATH_PI						= Real(3.1415926);
	
	//const Real MATH_REAL_MAX				= std::numeric_limits<Real>::max();
	//const Real MATH_REAL_MIN				= std::numeric_limits<Real>::min();
	const Real MATH_REAL_INFINITY			= std::numeric_limits<Real>::infinity();
	const Real MATH_REAL_EPSILON			= std::numeric_limits<Real>::epsilon();
}
#endif
