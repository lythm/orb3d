#pragma once


#include "input\SysInput.h"

namespace engine
{

	class Dx8Keyboard;
	class Dx8Mouse;
	class Dx8SysInput : public SysInput
	{
	public:
		Dx8SysInput(void);
		virtual ~Dx8SysInput(void);


		bool												Initialize(const SysInputParameters& param);
		void												Release();
		void												Update();

		const KeyState&										GetKeyState();
		const MouseState&									GetMouseState();

		//const JoystickState&								GetJoystickState();

	private:

		IDirectInput8*										m_pDInput;

		Dx8Keyboard*										m_pKeyboard;
		Dx8Mouse*											m_pMouse;

		KeyState											m_keyState;
		MouseState											m_mouseState;
		//JoystickState										m_joystickState;
	};


}