#pragma once

#include "input/sys_input.h"


namespace engine
{
	class DInput8Sys_Input : public Sys_Input
	{
	public:
		DInput8Sys_Input(void);
		virtual ~DInput8Sys_Input(void);


		bool										Initialize(const InputParameters& param);
		void										Release();


	private:
		LPDIRECTINPUT8								m_pDInput8;
		LPDIRECTINPUTDEVICE8						m_pDIKeyboard;
		LPDIRECTINPUTDEVICE8						m_pDIMouse;
	};


}