#include "game_pch.h"
#include "Game.h"



EXPORT_C_API Game* CreateGame()
{
	return new Game;
}

EXPORT_C_API void DestroyGame(engine::GameInterface* pGame)
{
	delete (Game*)pGame;
}



Game::Game(void)
{
	m_pDemo = NULL;
}


Game::~Game(void)
{
}
bool Game::Initialize(engine::CoreApiPtr pCore)
{
	m_pDemo = new DefferedShadingDemo;

	if(m_pDemo->Init(pCore) == false)
	{
		return false;
	}

	

	return true;
}
void Game::Release()
{

	m_pDemo->Release();
}
bool Game::Update()
{
	m_pDemo->Update();
	

	
	return true;
}
