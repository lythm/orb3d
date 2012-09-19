#include "Dx8Mouse.h"


namespace engine
{
	Dx8Mouse::Dx8Mouse(void)
	{
		m_pDInput			= NULL;
		m_pMouse			= NULL;

	}


	Dx8Mouse::~Dx8Mouse(void)
	{
	}

	bool Dx8Mouse::Initialize(IDirectInput8* pInput, void* app_handle)
	{
		m_pDInput = pInput;

		// Init mouse
		HRESULT hr = m_pDInput->CreateDevice( GUID_SysMouse, &m_pMouse, NULL );
		if( FAILED( hr ) )
		{
			return false;
		}

		hr = m_pMouse->SetCooperativeLevel( (HWND)app_handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
		if( FAILED( hr ) )
		{
			return false;
		}

		hr = m_pMouse->SetDataFormat( &c_dfDIMouse );
		if( FAILED( hr ) )
		{
			return false;
		}
		m_pMouse->Acquire( );

		return true;
	}
	void Dx8Mouse::Release()
	{
		if(m_pMouse)
		{
			m_pMouse->Release();
			m_pMouse = NULL;
		}

		m_pDInput = NULL;
	}
	bool Dx8Mouse::GetState(DIMOUSESTATE& state)
	{
		if(m_pMouse == NULL)
		{
			return false;
		}


		memset(&state, 0, sizeof(state));


		HRESULT hr = m_pMouse->GetDeviceState( sizeof( DIMOUSESTATE ), (LPVOID)&state );

		if( hr != DI_OK )
		{
			if( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED )
			{
				m_pMouse->Acquire( );
				
				hr = m_pMouse->GetDeviceState( sizeof( DIMOUSESTATE ), (LPVOID)&state );


			}
		}


		return true;
	}


}