#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelObject.h"

namespace engine
{
	VoxelObject::VoxelObject(GameObjectManagerPtr pManager) : GameObjectComponent(L"VoxelObject", pManager)
	{
	}


	VoxelObject::~VoxelObject(void)
	{
	}
	bool VoxelObject::OnAttach()
	{
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"VoxelObject");
		{
			
		}
		pPM->End();
		
		return true;
	}
	void VoxelObject::OnDetach()
	{
	}
}
