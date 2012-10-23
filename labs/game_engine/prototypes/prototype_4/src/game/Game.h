#pragma once


class Game : public engine::GameInterface
{
public:
	Game(void);
	virtual ~Game(void);

	bool									Initialize(engine::CoreApiPtr pCore);
	void									Release();
	bool									Update();

	

private:
	
	engine::CoreApiPtr								m_pCore;

	engine::GPUBufferPtr							m_pVB;
	engine::GPUBufferPtr							m_pIB;

	engine::GFXPtr									m_pGFX;

	
};

