#include "input_pch.h"
#include "DInput8Sys_Input.h"



extern "C" __declspec(dllexport) engine::Sys_Input* CreateSys()
{
	return new engine::DInput8Sys_Input;
}
extern "C" __declspec(dllexport) void DestroySys(engine::Sys_Input* pSys)
{
	delete (engine::DInput8Sys_Input*)pSys;
}
