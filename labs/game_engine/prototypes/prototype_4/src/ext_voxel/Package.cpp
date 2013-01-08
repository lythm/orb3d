#include "voxel_pch.h"

#include "Package.h"

#include "ext_voxel\VoxelData.h"
#include "ext_voxel\VoxelRenderer.h"


EXPORT_C_API engine::ExtPackage* CreatePackage(engine::CoreApiPtr pCore)
{
	return new engine::VoxelPackage(pCore);
}


EXPORT_C_API void DestroyPackage(engine::ExtPackage* pPackage)
{
	delete (engine::VoxelPackage*)pPackage;
}


namespace engine
{
	VoxelPackage::VoxelPackage(CoreApiPtr pCore)
	{
		
		m_pCore = pCore;

		m_classes.push_back(ComponentClass(L"VoxelData",
							L"Voxel",
							L"Voxel Data",
							&VoxelPackage::Create_VoxelData));
		m_classes.push_back(ComponentClass(L"VoxelRenderer",
							L"Voxel",
							L"Voxel Renderer",
							&VoxelPackage::Create_VoxelRenderer));
	}


	VoxelPackage::~VoxelPackage(void)
	{
	}

	std::wstring VoxelPackage::GetPackageName()
	{
		return L"Voxel";
	}
	
	int VoxelPackage::GetClassCount()
	{
		return (int)m_classes.size();
	}
	VoxelPackage::ComponentClass* VoxelPackage::GetClassByIndex(int index)
	{
		return &m_classes[index];
	}
	GameObjectComponentPtr VoxelPackage::Create_VoxelData(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<VoxelData, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr VoxelPackage::Create_VoxelRenderer(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<VoxelRenderer, GameObjectManagerPtr>(pManager);
	}
}
