#pragma once

#include "framework\GameInterface.h"


namespace engine
{
	class GameManager
	{
		
		typedef GameInterface*					(*Fn_CreateGame)();
		typedef void							(*Fn_DestroyGame)(GameInterface*);

	public:
		GameManager(void);
		virtual ~GameManager(void);

		bool									Initialize(const std::wstring& file);
		void									Release();

		GameInterface*							GetGame();

	private:
		
		
		HMODULE									m_hLib;
		std::wstring							m_filename;
		GameInterface*							m_pGame;
	};


}