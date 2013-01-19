#pragma once


namespace ld3d
{
	class Sys_Sound
	{
	public:
		Sys_Sound(void){}
		virtual ~Sys_Sound(void){}

		virtual bool								Initialize(int maxChannels)								= 0;
		virtual void								Release()												= 0;
		virtual void								Update()												= 0;
		virtual SoundChannelPtr						AllocChannel(SoundPtr pSound)							= 0;
		virtual SoundPtr							CreateSound(const char* szFile)							= 0;
		virtual SoundChannelPtr						CreateStream(const char* szFile)						= 0;
		virtual SoundPtr							Create3DSound(const char* szFile)						= 0;
		virtual SoundChannelPtr						Create3DStream(const char* szFile)						= 0;

		virtual void								SetListenerAttr(const math::Vector3& pos,
														const math::Vector3& vel,
														const math::Vector3& forward,
														const math::Vector3& up)							= 0;
	};
}
