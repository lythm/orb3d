#ifndef __ORBMATHTYPES__H__
#define __ORBMATHTYPES__H__

#include <cmath>
#include <limits>

#undef BYTE
#undef WORD
#undef DWORD

typedef unsigned char		byte;
typedef unsigned short		word;
typedef unsigned int		dword;


namespace math
{
#ifdef	__USE__DOUBLE__
	typedef		double		real;
#else
	typedef 	float		real;
#endif

	//! 常量定义
	const real PI				= real(3.14159265358979323846);
	const real TWO_PI			= real(2.0 * 3.14159265358979323846);
	const real HALF_PI			= real(3.14159265358979323846/ 2.0);

	const real EPSILON			= std::numeric_limits<real>::epsilon();
	const real POS_INF			= std::numeric_limits<real>::infinity();
}
#endif