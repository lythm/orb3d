#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelRenderer.h"

namespace engine
{
	VoxelRenderer::VoxelRenderer(GameObjectManagerPtr pManager) : GameObjectComponent(L"VoxelRenderer", pManager)
	{
	}


	VoxelRenderer::~VoxelRenderer(void)
	{
	}
	void VoxelRenderer::Update()
	{
		
	}

		
	bool VoxelRenderer::OnAttach()
	{
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"VoxelRenderer");
		{
			
		}
		pPM->End();

		return true;
	}
	void VoxelRenderer::OnDetach()
	{
		
	}
}
