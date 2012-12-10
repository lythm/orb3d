#include "core_pch.h"
#include "..\..\include\core\WorldMeshRenderer.h"
#include "core_utils.h"
namespace engine
{
	namespace object_component
	{
		WorldMeshRendererPtr WorldMeshRenderer::CreateComponent()
		{
			return alloc_object<WorldMeshRenderer>();
		}

		WorldMeshRenderer::WorldMeshRenderer(void) : GameObjectComponent(L"WorldMeshRenderer")
		{
		}


		WorldMeshRenderer::~WorldMeshRenderer(void)
		{
		}

	}

}
