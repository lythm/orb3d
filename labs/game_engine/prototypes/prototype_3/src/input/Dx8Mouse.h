#pragma once

namespace engine
{
	class Dx8Mouse
	{
	public:
		Dx8Mouse(void);
		virtual ~Dx8Mouse(void);

		bool											Initialize(IDirectInput8* pInput, void* app_handle);
		void											Release();
		bool											GetState(DIMOUSESTATE& state);
	private:
		IDirectInput8*									m_pDInput;
		IDirectInputDevice8*							m_pMouse;
	};


}