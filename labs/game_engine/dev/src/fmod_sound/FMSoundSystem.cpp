#include "fmsound_pch.h"
#include "FMSoundSystem.h"
#include "FMSound.h"
#include "FMSoundChannel.h"


EXPORT_C_API ld3d::Sys_Sound* CreateSys()
{
	return new ld3d::FMSoundSystem;
}

EXPORT_C_API void DestroySys(ld3d::Sys_Sound* pSys)
{
	delete (ld3d::FMSoundSystem*)pSys;
}


namespace ld3d
{
	FMSoundSystem::FMSoundSystem(void)
	{
		m_pSystem		= nullptr;

	}


	FMSoundSystem::~FMSoundSystem(void)
	{
	}
	bool FMSoundSystem::Initialize(int maxChannels)
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

		ret = m_pSystem->init(maxChannels, FMOD_INIT_NORMAL, 0);
		if(FMOD_OK != ret)
		{
			return false;
		}

		return true;
	}
	SoundPtr FMSoundSystem::Create3DSound(const char* szFile)
	{
		FMSound* pSound = new FMSound(m_pSystem);

		if(pSound->Create3D(szFile) == false)
		{
			delete pSound;
			return SoundPtr();
		}

		return SoundPtr(pSound);
	}
	SoundChannelPtr	FMSoundSystem::Create3DStream(const char* szFile)
	{
		FMOD::Sound* sound = nullptr;

		FMOD_RESULT ret = m_pSystem->createStream(szFile, FMOD_SOFTWARE | FMOD_3D, 0, &sound);
		if(ret != FMOD_OK)
		{
			return SoundChannelPtr();
		}
		
		FMSoundChannel* pChannel = new FMSoundChannel(m_pSystem);

		if(pChannel->Create(sound, true) == false)
		{
			delete pChannel;
			return SoundChannelPtr();
		}

		return SoundChannelPtr(pChannel);
	}
	SoundChannelPtr FMSoundSystem::CreateStream(const char* szFile)
	{
		FMOD::Sound* sound = nullptr;

		FMOD_RESULT ret = m_pSystem->createStream(szFile, FMOD_DEFAULT, 0, &sound);
		if(ret != FMOD_OK)
		{
			return SoundChannelPtr();
		}
		
		FMSoundChannel* pChannel = new FMSoundChannel(m_pSystem);

		if(pChannel->Create(sound, true) == false)
		{
			delete pChannel;
			return SoundChannelPtr();
		}

		return SoundChannelPtr(pChannel);
		
	}
	SoundPtr FMSoundSystem::CreateSound(const char* szFile)
	{
		FMSound* pSound = new FMSound(m_pSystem);

		if(pSound->Create(szFile) == false)
		{
			delete pSound;
			return SoundPtr();
		}

		return SoundPtr(pSound);
	}
	void FMSoundSystem::Release()
	{
		if(m_pSystem)
		{
			m_pSystem->release();
			m_pSystem = nullptr;
		}
	}
	void FMSoundSystem::Update()
	{
		m_pSystem->update();
	}
	SoundChannelPtr	FMSoundSystem::AllocChannel(SoundPtr pSound)
	{
		if(pSound == nullptr)
		{
			return SoundChannelPtr();
		}
		FMSound* pFMSound = (FMSound*)pSound.get();

		FMSoundChannel* pChannel = new FMSoundChannel(m_pSystem);

		if(pChannel->Create(pFMSound->GetFMSound()) == false)
		{
			delete pChannel;
			return SoundChannelPtr();
		}

		return SoundChannelPtr(pChannel);
	}
	void FMSoundSystem::SetListenerAttr(const math::Vector3& pos,
											const math::Vector3& vel,
											const math::Vector3& forward,
											const math::Vector3& up)
	{
		
		m_pSystem->set3DListenerAttributes(0, (FMOD_VECTOR*)&pos, (FMOD_VECTOR*)&vel, (FMOD_VECTOR*)&forward, (FMOD_VECTOR*)&up);
	}
}

