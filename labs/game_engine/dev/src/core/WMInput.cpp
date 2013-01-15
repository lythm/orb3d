#include "core_pch.h"
#include "WMInput.h"
#include <windowsx.h>

namespace ld3d
{
	WMInput::WMInput(void)
	{
	}


	WMInput::~WMInput(void)
	{
	}
	bool WMInput::Initialize(void* app_handle)
	{
		memset(&m_mouseState, 0, sizeof(m_mouseState));
		memset(&m_keyState, 0, sizeof(m_keyState));
		return true;
	}
	void WMInput::Release()
	{
	}
	void WMInput::Update()
	{
	}
			
	const WMInput::KeyState& WMInput::GetKeyState()
	{
		return m_keyState;
	}
	const WMInput::MouseState& WMInput::GetMouseState()
	{
		return m_mouseState;
	}
	void WMInput::HandleMessage(MSG& msg)
	{
		switch(msg.message)
		{
		case WM_INPUT:
			break;

		case WM_KEYUP:
			{

			}
			break;

		case WM_MOUSEMOVE:
			{
				int xPos = GET_X_LPARAM(msg.lParam); 
				int yPos = GET_Y_LPARAM(msg.lParam); 

				m_mouseState.x = xPos;
				m_mouseState.y = yPos;

			}
			break;

		default:
			break;
		}
	}
}
