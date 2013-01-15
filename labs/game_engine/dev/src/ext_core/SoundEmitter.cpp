#include "core_ext_pch.h"
#include "..\..\include\core\ext\SoundEmitter.h"



namespace ld3d
{

	SoundEmitter::SoundEmitter(GameObjectManagerPtr pManager):GameObjectComponent(L"SoundEmitter", pManager)
	{
	}


	SoundEmitter::~SoundEmitter(void)
	{
	}
}
