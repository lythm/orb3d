#pragma once

#include "core\Sys_Sound.h"

namespace ld3d
{
	class FMSoundSystem : public Sys_Sound
	{
	public:
		FMSoundSystem(void);
		virtual ~FMSoundSystem(void);

		bool								Initialize(int maxChannels);
		void								Release();
		void								Update();

		SoundPtr							CreateSound(const char* szFile);
		SoundChannelPtr						CreateStream(const char* szFile);

		SoundPtr							Create3DSound(const char* szFile);
		SoundChannelPtr						Create3DStream(const char* szFile);

		SoundChannelPtr						AllocChannel(SoundPtr pSound);

		void								SetListenerAttr(const math::Vector3& pos,
														const math::Vector3& vel,
														const math::Vector3& forward,
														const math::Vector3& up);
	private:
		FMOD::System*						m_pSystem;
	};
}
