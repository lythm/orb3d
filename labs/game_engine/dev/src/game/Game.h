#pragma once

#include "voxeldemo.h"

class Game : public ld3d::GameInterface
{
public:
	Game(void);
	virtual ~Game(void);

	bool									Initialize(ld3d::CoreApiPtr pCore);
	void									Release();
	bool									Update();

private:

	VoxelDemo*								m_pDemo;

	

};

