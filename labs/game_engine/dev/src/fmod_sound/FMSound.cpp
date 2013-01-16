#include "fmsound_pch.h"
#include "FMSound.h"


EXPORT_C_API ld3d::Sys_Sound* CreateSys()
{
	return new ld3d::FMSound;
}

EXPORT_C_API void DestroySys(ld3d::Sys_Sound* pSys)
{
	delete (ld3d::FMSound*)pSys;
}


namespace ld3d
{
	FMSound::FMSound(void)
	{
	}


	FMSound::~FMSound(void)
	{
	}
	bool FMSound::Initialize()
	{
		return true;
	}
	void FMSound::Release()
	{

	}
}

