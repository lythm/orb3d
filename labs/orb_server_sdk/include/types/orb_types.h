#ifndef _ORB_TYPES_H_
#define _ORB_TYPES_H_

#ifdef WIN32

#include "types/win_types.h"

#elif _WIN64

#include "types/win64_types.h"

#elif __FreeBSD__

#include "types/freebsd_types.h"

#elif LINUX

#endif

#include <map>
#include <list>
#include <vector>
#include <string>

namespace orb
{
	typedef unsigned char							uint8;
	typedef unsigned short							uint16;
	typedef unsigned int							uint32;

	typedef uint8									byte;

	typedef char									int8;
	typedef short									int16;
	typedef int										int32;

	typedef void*									kernel_object;

	const kernel_object invalid_kernel_object		= (kernel_object)-1;
}
#endif
