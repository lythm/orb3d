#include "core_pch.h"
#include "..\..\include\core\GameObjectComponent.h"


namespace engine
{
	GameObjectComponent::GameObjectComponent(void)
	{
		
	}


	GameObjectComponent::~GameObjectComponent(void)
	{
		m_pObject.reset();
	}
	void GameObjectComponent::Update()
	{
		
	}
	void GameObjectComponent::Attach(GameObjectPtr pObject)
	{
		m_pObject = pObject;
	}
	void GameObjectComponent::Detach()
	{
		m_pObject.reset();
	}
	const std::wstring& GameObjectComponent::GetName()
	{
		return m_name;
	}
}

