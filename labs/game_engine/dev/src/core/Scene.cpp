#include "core_pch.h"
#include "..\..\include\core\Scene.h"
#include "core\GameObject.h"
#include "core\GameObjectManager.h"
#include "core_utils.h"
#include "core\DataStream.h"
#include "core\GameObjectComponent.h"

namespace ld3d
{

	static const Version						g_scene_file_version = Version(0, 0, 0, 1);

	Scene::Scene(GameObjectManagerPtr pManager)
	{
		m_pObjectManager = pManager;
		m_pRoot = m_pObjectManager->CreateGameObject(L"_root");
	}


	Scene::~Scene(void)
	{
	}
	GameObjectPtr Scene::Root()
	{
		return m_pRoot;
	}
	void Scene::Reset()
	{
		m_pRoot->Clear();
		m_pRoot = m_pObjectManager->CreateGameObject(L"_root_");
	}
	void Scene::Release()
	{
		Reset();
		m_pRoot.reset();
	}
	void Scene::Update()
	{
		m_pRoot->Update();
	}
	
	bool Scene::Serialize(DataStream* pStream)
	{
		pStream->WriteInt32(g_scene_file_version.AsUInt32());

		return SerializeObject(m_pRoot, pStream);
	}
	bool Scene::UnSerialize(DataStream* pStream)
	{
		uint32 v = pStream->ReadInt32();

		if(Version(v) != g_scene_file_version)
		{
			return false;
		}

		return UnSerializeObject(m_pRoot, pStream);
	}
	bool Scene::SerializeObject(GameObjectPtr pObj, DataStream* pStream)
	{
		const std::wstring& name = pObj->GetName();
		pStream->WriteString(name);

		const math::Matrix44& local = pObj->GetLocalTransform();
		pStream->Write((void*)&local, sizeof(local));

		uint16 nCom = pObj->GetComponentCount() - 1;
		pStream->WriteInt16(nCom);

		for(int i = 0; i < nCom; ++i)
		{
			GameObjectComponentPtr pCom = pObj->GetComponent(i);
			
			if(pCom->GetName() == L"PropertyManager")
			{
				continue;
			}

			pStream->WriteString(pCom->GetName());
			
			if(false == pCom->Serialize(pStream))
			{
				return false;
			}
		}

		uint16 nChild = 0;

		GameObjectPtr pChild = pObj->GetFirstChild();

		while(pChild)
		{
			++nChild;
			pChild = pChild->GetNextNode();
		}

		pStream->WriteInt16(nChild);

		pChild = pObj->GetFirstChild();

		while(pChild)
		{
			SerializeObject(pChild, pStream);
			pChild = pChild->GetNextNode();
		}

		return true;
	}
	bool Scene::UnSerializeObject(GameObjectPtr pObj, DataStream* pStream)
	{
		std::wstring name;
		pStream->ReadString(name);
		pObj->SetName(name);

		math::Matrix44 local;
		pStream->Read(&local, sizeof(local));
		pObj->SetLocalTransform(local);

		uint16 nCom = 0;
		nCom = pStream->ReadInt16();

		for(uint16 i = 0; i < nCom; ++i)
		{
			std::wstring comName;
			pStream->ReadString(comName);

			
			GameObjectComponentPtr pCom = m_pObjectManager->CreateComponent(comName);
			if(pCom == nullptr)
			{
				return false;
			}
			pObj->AddComponent(pCom);

			pCom->UnSerialize(pStream);

		}
		
		uint16 nChild = 0;
		nChild = pStream->ReadInt16();
		for(uint16 i = 0; i < nChild; ++i)
		{
			GameObjectPtr pChild = m_pObjectManager->CreateGameObject(L"");
			UnSerializeObject(pChild, pStream);
			pChild->LinkTo(pObj);
		}
		
		return true;
	}
}

