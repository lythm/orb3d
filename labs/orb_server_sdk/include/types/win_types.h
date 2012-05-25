#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <assert.h>


#ifndef _WINDLL

#define _DLL_API				extern"C" __declspec(dllimport)
#define _DLL_CLASS				__declspec(dllimport)
#else

#define _DLL_API				extern"C" __declspec(dllexport)
#define _DLL_CLASS				__declspec(dllexport)
#endif


namespace orb
{

	typedef __int64									int64;
	typedef unsigned __int64						uint64;

	typedef wchar_t									w_char;
}