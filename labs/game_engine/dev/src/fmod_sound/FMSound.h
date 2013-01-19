#pragma once

namespace ld3d
{
	class FMSound : public Sound
	{
	public:
		FMSound(FMOD::System* pSystem);
		virtual ~FMSound(void);

		bool										Create(const char* szFile);
		bool										Create3D(const char* szFile);
		
		FMOD::Sound*								GetFMSound();

		void										Release();
		
	private:
		FMOD::System*								m_pSystem;
		FMOD::Sound *								m_pSound;
	};

}
