#pragma once


#include "core\Sys_Input.h"

#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>
#include "types\types.h"


namespace engine
{

	class Dx8Keyboard;
	class Dx8Mouse;
	class Dx8SysInput : public Sys_Input
	{
	public:
		Dx8SysInput(void);
		virtual ~Dx8SysInput(void);


		bool												Initialize(void* app_handle);
		void												Release();
		void												Update();

		const KeyState&										GetKeyState();
		const MouseState&									GetMouseState();

	private:

		IDirectInput8*										m_pDInput;

		Dx8Keyboard*										m_pKeyboard;
		Dx8Mouse*											m_pMouse;

		KeyState											m_keyState;
		MouseState											m_mouseState;
	};


}
