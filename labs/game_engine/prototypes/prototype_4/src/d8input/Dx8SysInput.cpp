#include "Dx8SysInput.h"
#include "types\dllexport.h"
#include "Dx8Keyboard.h"
#include "Dx8Mouse.h"


EXPORT_C_API engine::Sys_Input* CreateSys()
{
	return new engine::Dx8SysInput;
}

EXPORT_C_API void DestroySys(engine::Sys_Input* pSys)
{
	delete (engine::Dx8SysInput*)pSys;
}



namespace engine
{
	Dx8SysInput::Dx8SysInput(void)
	{
		m_pDInput = NULL;

		m_pKeyboard = NULL;

		memset(m_keyState.keys, 0, sizeof(uint8) * 256);
		memset(&m_mouseState, 0, sizeof(m_mouseState));
	}


	Dx8SysInput::~Dx8SysInput(void)
	{
	}


	bool Dx8SysInput::Initialize(void* app_handle)
	{
		HRESULT         hr; 

		hr = DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput, NULL ); 
		if( FAILED( hr ) )
		{ 
			return false;
		}

		m_pKeyboard = new Dx8Keyboard;

		if(m_pKeyboard == NULL ||
			m_pKeyboard->Initialize(m_pDInput, app_handle) == false)
		{
			return false;
		}

		m_pMouse = new Dx8Mouse;

		if(m_pMouse == NULL ||
			m_pMouse->Initialize(m_pDInput, app_handle) == false)
		{
			return false;
		}

		m_mouseState.x = 0;
		m_mouseState.y = 0;
		
		return true;
	}
	void Dx8SysInput::Release()
	{
		if(m_pKeyboard)
		{
			m_pKeyboard->Release();
			delete m_pKeyboard;
			m_pKeyboard = NULL;
		}

		if(m_pMouse)
		{
			m_pMouse->Release();
			delete m_pMouse;
			m_pMouse = NULL;
		}

		if(m_pDInput)
		{
			m_pDInput->Release();
			m_pDInput = false;
		}
	}
	void Dx8SysInput::Update()
	{
		if(m_pKeyboard)
		{
			m_pKeyboard->GetState(m_keyState.keys);
		}

		if(m_pMouse)
		{
			DIMOUSESTATE state;
			m_pMouse->GetState(state);

			m_mouseState.x = state.lX;
			m_mouseState.y = state.lY;
			m_mouseState.wheel = state.lZ;

			memcpy(m_mouseState.buttons, state.rgbButtons, sizeof(uint8) * 4);
		}
	}

	const Dx8SysInput::KeyState& Dx8SysInput::GetKeyState()
	{
		return m_keyState;
	}
	const Dx8SysInput::MouseState& Dx8SysInput::GetMouseState()
	{
		return m_mouseState;
	}

	
}



