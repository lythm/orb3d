#include "voxel_pch.h"

#include "VoxelPackage.h"

#include "ext_voxel\VoxelWorld.h"
#include "ext_voxel\VoxelWorldRenderer.h"
#include "VoxelWorldTemplate.h"


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





		// templates

		GameObjectTemplate* pTpl = new VoxelWorldTemplate(pCore->GetGameObjectManager(), L"VoxelWorld");
		m_tpls.push_back(pTpl);
	}


	VoxelPackage::~VoxelPackage(void)
	{
	}
	void VoxelPackage::Release()
	{
		m_classes.clear();
		for(size_t i = 0; i < m_tpls.size(); ++i)
		{
			m_tpls[i]->Release();
			delete m_tpls[i];
		}
		m_tpls.clear();
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
	int	VoxelPackage::GetTemplateCount()
	{
		return 1;
		//return (int)m_tpls.size();
	}
	GameObjectTemplate* VoxelPackage::GetTemplateByIndex(int index)
	{
		return m_tpls[index];
	}
}

