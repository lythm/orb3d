#pragma once

#include "DefferedShadingDemo.h"

class Game : public engine::GameInterface
{
public:
	Game(void);
	virtual ~Game(void);

	bool									Initialize(engine::CoreApiPtr pCore);
	void									Release();
	bool									Update();

private:

	DefferedShadingDemo*					m_pDemo;

};

