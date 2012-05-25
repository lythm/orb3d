#include "input_pch.h"
#include "DInput8Sys_Input.h"


namespace engine
{
	DInput8Sys_Input::DInput8Sys_Input(void)
	{
	}


	DInput8Sys_Input::~DInput8Sys_Input(void)
	{
	}
	bool DInput8Sys_Input::Initialize(const InputParameters& param)
	{
		HRESULT         hr; 

		hr = DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput8, NULL ); 
		if( FAILED( hr ) )
		{ 
			return false;
		}

		// Init keyboard
		hr = m_pDInput8->CreateDevice( GUID_SysKeyboard, &m_pDIKeyboard, NULL );
		if( FAILED( hr ) )
		{ 
			return false; 
		}

		hr = m_pDIKeyboard->SetCooperativeLevel((HWND) param.hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY );
		if( FAILED( hr ) )
		{ 
			return false; 
		}

		hr = m_pDIKeyboard->SetDataFormat( &c_dfDIKeyboard );
		if( FAILED( hr ) )
		{ 
			return false; 
		}
		m_pDIKeyboard->Acquire( );

		// Init mouse
		hr = m_pDInput8->CreateDevice( GUID_SysMouse, &m_pDIMouse, NULL );
		if( FAILED( hr ) )
		{
			return false;
		}

		hr = m_pDIMouse->SetCooperativeLevel((HWND) param.hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
		if( FAILED( hr ) )
		{
			return false;
		}

		hr = m_pDIMouse->SetDataFormat( &c_dfDIMouse );
		if( FAILED( hr ) )
		{
			return false;
		}
		m_pDIMouse->Acquire( );

		return true;
	}
	void DInput8Sys_Input::Release()
	{
		if(m_pDIKeyboard)
		{
			m_pDIKeyboard->Release();
			m_pDIKeyboard = NULL;
		}

		if(m_pDIMouse)
		{
			m_pDIMouse->Release();
			m_pDIMouse = NULL;
		}

		if(m_pDInput8)
		{
			m_pDInput8->Release();
			m_pDInput8 = NULL;
		}
	
	}
}