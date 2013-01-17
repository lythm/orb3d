#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelObjectRenderer.h"


namespace ld3d
{
	VoxelObjectRenderer::VoxelObjectRenderer(GameObjectManagerPtr pManager) : GameObjectComponent(L"VoxelObjectRenderer", pManager)
	{
	}


	VoxelObjectRenderer::~VoxelObjectRenderer(void)
	{
	}
	void VoxelObjectRenderer::Update()
	{
		
	}
	const Version& VoxelObjectRenderer::GetVersion() const
	{
		return g_packageVersion;
	}
		
	bool VoxelObjectRenderer::OnAttach()
	{
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"VoxelObjectRenderer");
		{
			
		}
		pPM->End();

		return true;
	}
	void VoxelObjectRenderer::OnDetach()
	{
		
	}
}
