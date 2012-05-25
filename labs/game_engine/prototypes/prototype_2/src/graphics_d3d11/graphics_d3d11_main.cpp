#include "graphics_pch.h"


#include "D3D11Sys_Graphics.h"




extern "C" __declspec(dllexport) engine::Sys_Graphics* CreateSys()
{
	return new engine::D3D11Sys_Graphics;
}
extern "C" __declspec(dllexport) void DestroySys(engine::Sys_Graphics* pSys)
{
	delete (engine::D3D11Sys_Graphics*)pSys;
}
