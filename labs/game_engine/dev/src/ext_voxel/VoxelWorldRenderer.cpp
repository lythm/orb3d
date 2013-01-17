#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelWorldRenderer.h"
#include "VoxelWorldRenderData.h"

namespace ld3d
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

	const Version& VoxelWorldRenderer::GetVersion() const
	{
		return g_packageVersion;
	}
	bool VoxelWorldRenderer::OnAttach()
	{
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"VoxelWorldRenderer");
		{
			
		}
		pPM->End();


		m_pRenderData = m_pManager->GetAllocator()->AllocObject<VoxelWorldRenderData>();
		if(m_pRenderData->Initialize() == false)
		{
			return false;
		}
		return true;
	}
	void VoxelWorldRenderer::OnDetach()
	{
		m_pRenderData->Release();
		m_pRenderData.reset();
	}
}
