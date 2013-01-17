#include "voxel_pch.h"

#include "VoxelPackage.h"

#include "ext_voxel\VoxelWorld.h"
#include "ext_voxel\VoxelWorldRenderer.h"
#include "ext_voxel\VoxelObject.h"
#include "ext_voxel\VoxelObjectRenderer.h"


#include "VoxelWorldTemplate.h"
#include "VoxelObjectTemplate.h"


EXPORT_C_API ld3d::ExtPackage* CreatePackage(ld3d::CoreApiPtr pCore)
{
	return new ld3d::VoxelPackage(pCore);
}


EXPORT_C_API void DestroyPackage(ld3d::ExtPackage* pPackage)
{
	delete (ld3d::VoxelPackage*)pPackage;
}

namespace ld3d
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

		m_classes.push_back(ComponentClass(L"VoxelObject",
							L"Voxel",
							L"Voxel Object",
							&VoxelPackage::Create_VoxelObject));
		m_classes.push_back(ComponentClass(L"VoxelObjectRenderer",
							L"Voxel",
							L"Voxel Object Renderer",
							&VoxelPackage::Create_VoxelObjectRenderer));

		// templates
		GameObjectTemplate* pTpl = new VoxelWorldTemplate(pCore->GetGameObjectManager(), L"VoxelWorld");
		m_tpls.push_back(pTpl);

		pTpl = new VoxelObjectTemplate(pCore->GetGameObjectManager(), L"VoxelObject");
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
	const wchar_t* VoxelPackage::GetPackageName()
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

	GameObjectComponentPtr VoxelPackage::Create_VoxelObject(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<VoxelObject, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr VoxelPackage::Create_VoxelObjectRenderer(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<VoxelObjectRenderer, GameObjectManagerPtr>(pManager);
	}
	int	VoxelPackage::GetTemplateCount()
	{
		return (int)m_tpls.size();
	}
	GameObjectTemplate* VoxelPackage::GetTemplateByIndex(int index)
	{
		return m_tpls[index];
	}
}

