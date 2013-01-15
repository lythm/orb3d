#pragma once

#include "DefferedShadingDemo.h"

class Game : public ld3d::GameInterface
{
public:
	Game(void);
	virtual ~Game(void);

	bool									Initialize(ld3d::CoreApiPtr pCore);
	void									Release();
	bool									Update();

private:

	DefferedShadingDemo*					m_pDemo;

};

