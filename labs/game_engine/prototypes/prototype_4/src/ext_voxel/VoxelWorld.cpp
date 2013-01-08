#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelWorld.h"


namespace engine
{
	VoxelWorld::VoxelWorld(GameObjectManagerPtr pManager) : GameObjectComponent(L"VoxelWorld", pManager)
	{
		m_unitSize = 1.0f;
	}


	VoxelWorld::~VoxelWorld(void)
	{
	}
	void VoxelWorld::Update()
	{
		
	}

		
	bool VoxelWorld::OnAttach()
	{
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"VoxelWorld");
		{
			pPM->RegisterProperty<float, VoxelWorld>(this,
									L"Unit Size",
									&VoxelWorld::GetUnitSize,
									&VoxelWorld::SetUnitSize);
		}
		pPM->End();






		return true;
	}
	const float& VoxelWorld::GetUnitSize()
	{
		return m_unitSize;
	}
	void VoxelWorld::SetUnitSize(const float& size)
	{
		m_unitSize = size;
	}
	void VoxelWorld::OnDetach()
	{
		
	}
	void VoxelWorld::AddBlock()
	{
	}
	void VoxelWorld::RemoveBlock()
	{
	}

}
