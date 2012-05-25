#pragma once

#ifdef _WINDLL

#define DLL_EXPORT		__declspec(dllexport)

#else

#define DLL_EXPORT		__declspec(dllimport)

#endif


#include <windows.h>
#include <string>