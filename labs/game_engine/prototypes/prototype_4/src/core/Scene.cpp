#include "core_pch.h"
#include "..\..\include\core\Scene.h"
#include "core\GameObject.h"
#include "core\GameObjectManager.h"
#include "core_utils.h"

namespace engine
{
	Scene::Scene(void)
	{
		m_pRoot = alloc_object<GameObject, wchar_t*>(L"_root");
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
	bool Scene::Load(DataStreamPtr pStream)
	{
		
		return true;
	}
}
