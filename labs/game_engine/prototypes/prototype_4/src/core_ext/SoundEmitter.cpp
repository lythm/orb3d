#include "core_ext_pch.h"
#include "..\..\include\core\ext\SoundEmitter.h"



namespace engine
{

	SoundEmitter::SoundEmitter(GameObjectManagerPtr pManager):GameObjectComponent(L"SoundEmitter", pManager)
	{
	}


	SoundEmitter::~SoundEmitter(void)
	{
	}
}
