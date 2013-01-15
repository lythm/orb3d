#include "pch.h"
#include "GameManager.h"


namespace ld3d
{
	GameManager::GameManager(void)
	{
		m_hLib				= NULL;
		m_pGame				= NULL;
	}


	GameManager::~GameManager(void)
	{
	}
	bool GameManager::Initialize(const std::wstring& file)
	{
		m_hLib = ::LoadLibrary(file.c_str());

		if(m_hLib == NULL)
		{
			return false;
		}

		Fn_CreateGame CreateGame = (Fn_CreateGame)GetProcAddress(m_hLib, "CreateGame");

		if(CreateGame == NULL)
		{
			return false;
		}
		m_filename = file;

		m_pGame = CreateGame();

		if(m_pGame == NULL)
		{
			return false;
		}
		return true;
	}
	void GameManager::Release()
	{
		if(m_hLib == NULL)
		{
			return;
		}
		Fn_DestroyGame DestroyGame = (Fn_DestroyGame)GetProcAddress(m_hLib, "DestroyGame");

		if(DestroyGame != NULL)
		{
			DestroyGame(m_pGame);
		}


		FreeLibrary(m_hLib);
		m_hLib = NULL;
	}

	GameInterface* GameManager::GetGame()
	{
		return m_pGame;
	}
}