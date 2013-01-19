#pragma once

namespace ld3d
{
	class SoundChannel
	{
	public:

		virtual void							Play(bool bLoop = false)						= 0;
		virtual void							Stop()											= 0;
		virtual void							Pause()											= 0;
		virtual void							Release()										= 0;
		virtual void							SetLoop(bool bLoop)								= 0;
		virtual void							SetPosition(float x, float y, float z)			= 0;
		virtual void							SetVelocity(float x, float y, float z)			= 0;
		virtual void							SetVolume(float v)								= 0;
		virtual void							SetMinDistance(float d)							= 0;
		virtual void							SetMaxDistance(float d)							= 0;
		virtual float							GetLength()										= 0;
		virtual void							SetTime(float sec)								= 0;
		virtual void							SetPriority(int p)								= 0;
		virtual bool							GetMute()										= 0;
		virtual void							SetMute(bool bMute)								= 0;
		virtual void							SetPan(float pan)								= 0;
	protected:
		SoundChannel(void){}
		virtual ~SoundChannel(void){}
	};
}
