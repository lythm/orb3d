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

}


Game::~Game(void)
{
}
bool Game::Initialize(engine::GameEnginePtr pEngine)
{
	m_pGameEngine = pEngine;

	m_pRenderData = m_pGameEngine->GetSysGraphics()->CreateRenderData();


	m_pRenderData->AllocIndexBuffer(12, NULL, true);
	m_pRenderData->AllocVertexBuffer(1024, NULL, true);


	//m_pShader = m_pGameEngine->GetSysGraphics()->CreateShader();

		
	//m_pShader->LoadFromFile("./assets/shaders/test.cgfx");

//	m_pRenderData->SetShader(m_pShader);

	engine::VertexElement format[] = 
	{
		engine::VertexElement(0, engine::VertexElement::POSITION, engine::VertexElement::VE_FLOAT3),
		engine::VertexElement(0, engine::VertexElement::TEXCOORD, engine::VertexElement::VE_FLOAT2),
	};
	
//	m_pShader->SetVertexFormat(format, 2);

	return true;
}
void Game::Release()
{
//	m_pRenderData->Release();
}
bool Game::Update()
{
	using namespace engine;

	//m_pGameEngine->GetSysInput()->Update();

	const engine::SysInput::KeyState& keys = m_pGameEngine->GetSysInput()->GetKeyState();
	
	if(keys.KeyDown(SysInput::key_escape))
	{
		return false;
	}

	const engine::SysInput::MouseState& mouse = m_pGameEngine->GetSysInput()->GetMouseState();

	
	//m_pGameEngine->GetSysGraphics()->PushRenderData(m_pRenderData);


	struct TTT
	{
		int a;
	};


	boost::shared_ptr<TTT> pT = m_pGameEngine->GetEngineCore()->ObjectAlloc<TTT>();


	return true;
}
