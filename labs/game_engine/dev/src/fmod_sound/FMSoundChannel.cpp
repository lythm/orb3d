#include "fmsound_pch.h"
#include "FMSoundChannel.h"

namespace ld3d
{
	FMSoundChannel::FMSoundChannel(FMOD::System* pSys)
	{
		m_bStream = false;
		m_pSystem = pSys;
		m_pChannel = nullptr;
		m_volume = 1.0f;

		memset(&m_pos, 0, sizeof(FMOD_VECTOR));
		memset(&m_velocity, 0, sizeof(FMOD_VECTOR));

		m_minDist			= 1.0f;
		m_maxDist			= 10000.0f;

		m_priority			= 0;
		m_time				= 0;
		m_pan				= 0;
		m_mute				= false;

	}


	FMSoundChannel::~FMSoundChannel(void)
	{
	}
	void FMSoundChannel::Release()
	{
		if(m_pChannel)
		{
			m_pChannel->stop();
			m_pChannel = nullptr;
		}

		if(m_bStream && m_pSound)
		{
			m_pSound->release();
			m_pSound = nullptr;
		}
	}
	FMOD::Channel* FMSoundChannel::GetFMChannel()
	{
		return m_pChannel;
	}
	bool FMSoundChannel::Create(FMOD::Sound* pSound, bool bStream)
	{
		m_bStream = bStream;
		m_pSound = pSound;
		return true;
	}
	void FMSoundChannel::Play(bool bLoop)
	{
		if(m_pSound == nullptr || m_pSystem == nullptr)
		{
			return;
		}
		SetLoop(bLoop);

		if(m_pChannel == nullptr)
		{
			m_pSystem->playSound(FMOD_CHANNEL_FREE, m_pSound, true, &m_pChannel);
			UpdateChannel();
		}
		
		m_pChannel->setPaused(false);
	}
	void FMSoundChannel::Stop()
	{
		if(m_pChannel)
		{
			m_pChannel->stop();
			m_pChannel = nullptr;
		}
	}
	void FMSoundChannel::Pause()
	{
		if(m_pChannel)
		{
			m_pChannel->setPaused(true);
		}
	}
	void FMSoundChannel::SetLoop(bool bLoop)
	{
		m_bLoop = bLoop;

		if(m_pChannel == nullptr)
		{
			return;
		}

		m_pChannel->setMode(m_bLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
		m_pChannel->setLoopCount(m_bLoop ? -1 : 0);
	}
	void FMSoundChannel::UpdateChannel()
	{
		if(m_pChannel == nullptr)
		{
			return;
		}

		SetLoop(m_bLoop);
		SetPosition(m_pos.x, m_pos.y, m_pos.z);
		SetVelocity(m_velocity.x, m_velocity.y, m_velocity.z);
		SetVolume(m_volume);
		SetMinDistance(m_minDist);
		SetMaxDistance(m_maxDist);
		SetTime(m_time);
		SetPriority(m_priority);
		SetPan(m_pan);
		SetMute(m_mute);
	}
	void FMSoundChannel::SetPosition(float x, float y, float z)
	{
		m_pos.x = x;
		m_pos.y = y;
		m_pos.z = z;

		if(m_pChannel == nullptr)
		{
			return;
		}

		m_pChannel->set3DAttributes(&m_pos, &m_velocity);
	}
	void FMSoundChannel::SetVelocity(float x, float y, float z)
	{
		m_velocity.x = x;
		m_velocity.y = y;
		m_velocity.z = z;

		if(m_pChannel == nullptr)
		{
			return;
		}

		m_pChannel->set3DAttributes(&m_pos, &m_velocity);
	}
	void FMSoundChannel::SetVolume(float v)
	{
		m_volume = v;
		if(m_pChannel == nullptr)
		{
			return;
		}

		m_pChannel->setVolume(m_volume);
	}
	void FMSoundChannel::SetMinDistance(float d)
	{
		m_minDist = d;
		if(m_pChannel == nullptr)
		{
			return;
		}

		m_pChannel->set3DMinMaxDistance(m_minDist, m_maxDist);
	}
	void FMSoundChannel::SetMaxDistance(float d)
	{
		m_maxDist = d;

		if(m_pChannel == nullptr)
		{
			return;
		}

		m_pChannel->set3DMinMaxDistance(m_minDist, m_maxDist);
	}
	float FMSoundChannel::GetLength()
	{
		if(m_pSound == nullptr)
		{
			return 0;
		}

		unsigned int len = 0;
		m_pSound->getLength(&len, FMOD_TIMEUNIT_MS);

		return float(len) / 1000.0f;
	}
	void FMSoundChannel::SetTime(float sec)
	{
		m_time = 0;
		if(m_pChannel == nullptr)
		{
			return;
		}

		unsigned int pos = (unsigned int)(sec * 1000);
		m_pChannel->setPosition(pos, FMOD_TIMEUNIT_MS);
	}
	void FMSoundChannel::SetPriority(int p)
	{
		m_priority = p;
		if(m_pChannel == nullptr)
		{
			return;
		}

		m_pChannel->setPriority(m_priority);
	}

	bool FMSoundChannel::GetMute()
	{
		return m_mute;
	}
	void FMSoundChannel::SetMute(bool bMute)
	{
		m_mute = bMute;
		if(m_pChannel == nullptr)
		{
			return;
		}

		m_pChannel->setMute(bMute);
	}
	void FMSoundChannel::SetPan(float pan)
	{
		m_pan = pan;
		if(m_pChannel == nullptr)
		{
			return;
		}

		m_pChannel->setPan(pan);
	}
}
