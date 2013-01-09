#include "voxel_pch.h"

#include "Package.h"

#include "ext_voxel\VoxelWorld.h"
#include "ext_voxel\VoxelWorldRenderer.h"


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

		m_classes.push_back(ComponentClass(L"VoxelWorld",
							L"Voxel",
							L"Voxel World",
							&VoxelPackage::Create_VoxelWorld));
		m_classes.push_back(ComponentClass(L"VoxelWorldRenderer",
							L"Voxel",
							L"Voxel World Renderer",
							&VoxelPackage::Create_VoxelWorldRenderer));
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
	GameObjectComponentPtr VoxelPackage::Create_VoxelWorld(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<VoxelWorld, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr VoxelPackage::Create_VoxelWorldRenderer(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<VoxelWorldRenderer, GameObjectManagerPtr>(pManager);
	}
}
