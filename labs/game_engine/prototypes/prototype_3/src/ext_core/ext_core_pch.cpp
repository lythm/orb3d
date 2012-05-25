#include "ext_core_pch.h"


#define WIN32_LEAN_AND_MEAN

#include <Windows.h>


#include "Ext_Core.h"



EXPORT_C_API engine::Extension* CreateExtension()
{
	return new engine::Ext_Core;
}

EXPORT_C_API void DestroyExtension(engine::Extension* pExt)
{
	delete (engine::Ext_Core*)pExt;
}
