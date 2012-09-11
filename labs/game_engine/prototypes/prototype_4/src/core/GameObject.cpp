#include "core_pch.h"
#include "..\..\include\core\GameObject.h"
#include "core\GameObjectComponent.h"

namespace engine
{
	GameObject::GameObject(void)
	{
	}


	GameObject::~GameObject(void)
	{
		for(size_t i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->Attach(GameObjectPtr());
		}

		m_components.clear();
	}
	void GameObject::Update()
	{
		GameObjectPtr pObj = boost::shared_dynamic_cast<GameObject>(GetFirstChild());

		while(pObj)
		{
			pObj->Update();
			pObj = boost::shared_dynamic_cast<GameObject>(pObj->GetNextNode());
		}

		UpdateComponents();
	}
	GameObjectPtr GameObject::ThisPtr()
	{
		return GameObjectPtr(boost::shared_dynamic_cast<GameObject>(shared_from_this()));
	}
	void GameObject::AddComponent(GameObjectComponentPtr pCom)
	{
		pCom->Attach(ThisPtr());

		m_components.push_back(pCom);
	}
	void GameObject::UpdateComponents()
	{
		for(size_t i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->Update();
		}
	}
	GameObjectComponentPtr GameObject::GetComponent(const char* szName)
	{
		for(size_t i = 0; i < m_components.size(); ++i)
		{
			if(m_components[i]->GetName() == std::string(szName))
			{
				return m_components[i];
			}
		}

		return GameObjectComponentPtr();
	}
}
