#include "fmsound_pch.h"
#include "FMSound.h"

namespace ld3d
{
	FMSound::FMSound(FMOD::System* pSystem)
	{
		m_pSystem				= pSystem;
		m_pSound				= nullptr;
	}


	FMSound::~FMSound(void)
	{
	}
	bool FMSound::Create(const char* szFile)
	{
		FMOD_RESULT ret = m_pSystem->createSound(szFile, FMOD_DEFAULT, 0, &m_pSound);
		if(ret != FMOD_OK)
		{
			return false;
		}

		return true;
	}
	bool FMSound::Create3D(const char* szFile)
	{
		FMOD_RESULT ret = m_pSystem->createSound(szFile, FMOD_HARDWARE | FMOD_3D, 0, &m_pSound);
		if(ret != FMOD_OK)
		{
			return false;
		}

		return true;
	}
	
	void FMSound::Release()
	{
		if(m_pSound)
		{
			m_pSound->release();
			m_pSound = nullptr;
		}
	}
		
	FMOD::Sound* FMSound::GetFMSound()
	{
		return m_pSound;
	}
}
