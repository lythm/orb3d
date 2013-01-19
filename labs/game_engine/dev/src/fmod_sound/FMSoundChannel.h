#pragma once


namespace ld3d
{
	class FMSoundChannel : public SoundChannel
	{
	public:
		FMSoundChannel(FMOD::System* pSys);
		virtual ~FMSoundChannel(void);

		
		FMOD::Channel*					GetFMChannel();
		bool							Create(FMOD::Sound* pSound, bool bStream = false);
		
		void							Release();
		void							Play(bool bLoop = false);
		void							Stop();
		void							Pause();

		void							SetLoop(bool bLoop);

		void							SetPosition(float x, float y, float z);
		void							SetVelocity(float x, float y, float z);
		void							SetVolume(float v);

		void							SetMinDistance(float d);
		void							SetMaxDistance(float d);

		float							GetLength();
		void							SetTime(float sec);

		void							SetPriority(int p);

		bool							GetMute();
		void							SetMute(bool bMute);
		void							SetPan(float pan);
	private:
		void							UpdateChannel();
	private:
		FMOD::Sound*					m_pSound;
		FMOD::Channel*					m_pChannel;
		FMOD::System*					m_pSystem;


		bool							m_bLoop;

		bool							m_bStream;
		
		FMOD_VECTOR						m_pos;
		FMOD_VECTOR						m_velocity;

		float							m_volume;

		float							m_minDist;
		float							m_maxDist;

		int								m_priority;
		float							m_time;

		float							m_pan;
		bool							m_mute;
	};
}
