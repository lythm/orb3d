#include "Dx8Keyboard.h"


namespace engine
{

	Dx8Keyboard::Dx8Keyboard(void)
	{
		m_pDInput			= NULL;
		m_pKeyboard			= NULL;
	}


	Dx8Keyboard::~Dx8Keyboard(void)
	{
	}

	bool Dx8Keyboard::Initialize(IDirectInput8* pInput, void* app_handle)
	{
		m_pDInput = pInput;
		// Init keyboard
		HRESULT hr = m_pDInput->CreateDevice( GUID_SysKeyboard, &m_pKeyboard, NULL );
		if( FAILED( hr ) )
		{ 
			return false; 
		}

		hr = m_pKeyboard->SetCooperativeLevel((HWND)app_handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY );
		if( FAILED( hr ) )
		{ 
			return false; 
		}

		hr = m_pKeyboard->SetDataFormat( &c_dfDIKeyboard );
		if( FAILED( hr ) )
		{ 
			return false; 
		}
		m_pKeyboard->Acquire( );

		return true;
	}
	void Dx8Keyboard::Release()
	{
		if(m_pKeyboard)
		{
			m_pKeyboard->Release();
			m_pKeyboard = NULL;
		}
		m_pDInput = NULL;
	}

	bool Dx8Keyboard::GetState(uint8 state[256])
	{
		if(m_pKeyboard == NULL)
		{
			return false;
		}

		memset(state, 0, sizeof(uint8) * 256);

		HRESULT hr = m_pKeyboard->GetDeviceState( sizeof( BYTE ) * 256, (LPVOID)state );

		if( hr != DI_OK )
		{
			if( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED )
			{
				m_pKeyboard->Acquire( );
				m_pKeyboard->GetDeviceState( sizeof( BYTE ) * 256, (LPVOID)state );
			}
		}


		return true;
	}
}
