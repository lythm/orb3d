#include "core_ext_pch.h"
#include "..\..\include\core\ext\SoundListener.h"

namespace ld3d
{

	SoundListener::SoundListener(GameObjectManagerPtr pManager) : GameObjectComponent(L"SoundListener", pManager)
	{
	}


	SoundListener::~SoundListener(void)
	{
	}
}
