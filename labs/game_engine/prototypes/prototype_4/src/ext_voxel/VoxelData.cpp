#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelData.h"

namespace engine
{
	VoxelData::VoxelData(GameObjectManagerPtr pManager) : GameObjectComponent(L"VoxelData", pManager)
	{
	}


	VoxelData::~VoxelData(void)
	{
	}
	void VoxelData::Update()
	{
		
	}

		
	bool VoxelData::OnAttach()
	{
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"VoxelData");
		{
			
		}
		pPM->End();

		return true;
	}
	void VoxelData::OnDetach()
	{
		
	}

}