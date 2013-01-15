#include "voxel_pch.h"
#include "VoxelObjectTemplate.h"



namespace engine
{
	VoxelObjectTemplate::VoxelObjectTemplate(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Voxel")
	{
		
	}
	
	VoxelObjectTemplate::~VoxelObjectTemplate(void)
	{
	}
	
	GameObjectPtr VoxelObjectTemplate::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"VoxelObject");

		GameObjectComponentPtr pCom = m_pManager->CreateComponent(L"VoxelObject");

		pObj->AddComponent(pCom);

		pCom = m_pManager->CreateComponent(L"VoxelObjectRenderer");
		pObj->AddComponent(pCom);

		return pObj;
	}
	void VoxelObjectTemplate::Release()
	{
	}
}

