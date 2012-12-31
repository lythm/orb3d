#include "core_ext_pch.h"
#include "..\..\include\core\ext\Camera.h"

namespace engine
{
	Camera::Camera(GameObjectManagerPtr pManager) : GameObjectComponent(L"Camera", pManager)
	{
	}


	Camera::~Camera(void)
	{
	}

}
