#include "core_ext_pch.h"
#include "..\..\include\core\ext\WorldMeshRenderer.h"
#include "CorePackage.h"

namespace ld3d
{

	WorldMeshRenderer::WorldMeshRenderer(GameObjectManagerPtr pManager) : GameObjectComponent(L"WorldMeshRenderer", pManager)
	{
	}


	WorldMeshRenderer::~WorldMeshRenderer(void)
	{
	}

}

