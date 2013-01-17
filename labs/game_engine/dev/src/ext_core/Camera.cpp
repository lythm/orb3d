#include "core_ext_pch.h"
#include "..\..\include\core\ext\Camera.h"

namespace ld3d
{
	Camera::Camera(GameObjectManagerPtr pManager) : GameObjectComponent(L"Camera", pManager)
	{
	}


	Camera::~Camera(void)
	{
	}
	const Version& Camera::GetVersion() const
	{
		return g_packageVersion;
	}
}
