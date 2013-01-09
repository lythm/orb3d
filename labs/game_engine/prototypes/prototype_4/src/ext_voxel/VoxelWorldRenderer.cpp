#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelWorldRenderer.h"

namespace engine
{
	VoxelWorldRenderer::VoxelWorldRenderer(GameObjectManagerPtr pManager) : GameObjectComponent(L"VoxelWorldRenderer", pManager)
	{
	}


	VoxelWorldRenderer::~VoxelWorldRenderer(void)
	{
	}
	void VoxelWorldRenderer::Update()
	{
		
	}

		
	bool VoxelWorldRenderer::OnAttach()
	{
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"VoxelRenderer");
		{
			
		}
		pPM->End();

		return true;
	}
	void VoxelWorldRenderer::OnDetach()
	{
		
	}
}
