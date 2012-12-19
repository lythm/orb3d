#include "core_ext_pch.h"
#include "..\..\include\core\ext\WorldMeshRenderer.h"
#include "Package.h"

namespace engine
{

	WorldMeshRendererPtr WorldMeshRenderer::CreateComponent()
	{
		return Package::GetAllocator()->AllocObject<WorldMeshRenderer>();
	}

	WorldMeshRenderer::WorldMeshRenderer(void) : GameObjectComponent(L"WorldMeshRenderer")
	{
	}


	WorldMeshRenderer::~WorldMeshRenderer(void)
	{
	}

}

