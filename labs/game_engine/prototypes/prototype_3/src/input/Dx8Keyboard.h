#pragma once


namespace engine
{
	class Dx8Keyboard
	{
	public:
		Dx8Keyboard(void);
		virtual ~Dx8Keyboard(void);

		bool											Initialize(IDirectInput8* pInput, void* app_handle);
		void											Release();
		bool											GetState(uint8 state[256]);
	private:
		IDirectInput8*									m_pDInput;

		IDirectInputDevice8*							m_pKeyboard;
	};
}