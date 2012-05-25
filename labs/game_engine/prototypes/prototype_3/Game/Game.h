#pragma once




class Game : public engine::GameInterface
{
public:
	Game(void);
	virtual ~Game(void);

	bool									Initialize(engine::GameEnginePtr pEngine);
	void									Release();
	bool									Update();

	

private:
	
	engine::GameEnginePtr					m_pGameEngine;

	engine::RenderDataPtr					m_pRenderData;

	engine::ShaderPtr						m_pShader;
};

