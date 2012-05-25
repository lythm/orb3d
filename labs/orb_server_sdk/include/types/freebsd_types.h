#ifndef _FREEBSD_TYPES_H_
#define _FREEBSD_TYPES_H_

#include <sys/types.h>
#include <wchar.h>


#define _DLL_API									extern"C"
#define _DLL_CLASS


namespace orb
{

	typedef long long								int64;
	typedef unsigned long long						uint64;

	typedef wchar_t									w_char;

}
#endif
