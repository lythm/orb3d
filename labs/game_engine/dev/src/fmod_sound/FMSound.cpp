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
		m_pSystem		= nullptr;

	}


	FMSound::~FMSound(void)
	{
	}
	bool FMSound::Initialize()
	{
		FMOD_RESULT ret = FMOD::System_Create(&m_pSystem);
		if(ret != FMOD_OK)
		{
			return false;
		}

		ret = m_pSystem->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);	// Set the output to 5.1.
		if(ret != FMOD_OK)
		{
			return false;
		}

		ret = m_pSystem->setSoftwareChannels(100);		// Allow 100 software mixed voices to be audible at once.
		if(ret != FMOD_OK)
		{
			return false;
		}

		ret = m_pSystem->setHardwareChannels(32, 64, 32, 64);	// Require the soundcard to have at least 32 2D and 3D hardware voices, and clamp it to using 64 if it has more than this.
		if(ret != FMOD_OK)
		{
			return false;
		}

		ret = m_pSystem->init(1000, FMOD_INIT_NORMAL, 0);
		if(FMOD_OK != ret)
		{
			return false;
		}

		return true;
	}
	void FMSound::Release()
	{
		if(m_pSystem)
		{
			m_pSystem->release();
			m_pSystem = nullptr;
		}
	}
	void FMSound::Update()
	{
		m_pSystem->update();
	}
}

