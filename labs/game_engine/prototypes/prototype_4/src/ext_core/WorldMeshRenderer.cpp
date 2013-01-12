#include "core_ext_pch.h"
#include "..\..\include\core\ext\WorldMeshRenderer.h"
#include "CorePackage.h"

namespace engine
{

	WorldMeshRenderer::WorldMeshRenderer(GameObjectManagerPtr pManager) : GameObjectComponent(L"WorldMeshRenderer", pManager)
	{
	}


	WorldMeshRenderer::~WorldMeshRenderer(void)
	{
	}

}

