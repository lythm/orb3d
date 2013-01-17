#include "voxel_pch.h"
#include "VoxelWorldTemplate.h"
#include "ext_voxel\VoxelWorld.h"
#include "ext_voxel\VoxelWorldRenderer.h"

namespace ld3d
{
	VoxelWorldTemplate::VoxelWorldTemplate(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Voxel")
	{
		
	}
	
	VoxelWorldTemplate::~VoxelWorldTemplate(void)
	{
	}
	
	GameObjectPtr VoxelWorldTemplate::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"VoxelWorld");

		VoxelWorldPtr pWorld = m_pManager->GetAllocator()->AllocObject<VoxelWorld>(m_pManager);

		pObj->AddComponent(pWorld);

		pWorld->Generate();

		VoxelWorldRendererPtr pRenderer = m_pManager->GetAllocator()->AllocObject<VoxelWorldRenderer>(m_pManager);
		pObj->AddComponent(pRenderer);

		return pObj;
	}
	void VoxelWorldTemplate::Release()
	{
	}
}

