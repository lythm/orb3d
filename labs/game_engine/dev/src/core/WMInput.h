#pragma once

#include "core\Sys_Input.h"


namespace ld3d
{
	class WMInput : public Sys_Input
	{
	public:
		WMInput(void);
		virtual ~WMInput(void);


		bool												Initialize(void* app_handle);
		void												Release();
		void												Update();

		
		const KeyState&										GetKeyState();
		const MouseState&									GetMouseState();

		void												HandleMessage(MSG& msg);


	private:
		KeyState											m_keyState;
		MouseState											m_mouseState;
	};


}