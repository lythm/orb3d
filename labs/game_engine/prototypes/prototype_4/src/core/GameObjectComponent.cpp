#include "core_pch.h"
#include "..\..\include\core\GameObjectComponent.h"


namespace engine
{
	GameObjectComponent::GameObjectComponent(void)
	{
		
	}


	GameObjectComponent::~GameObjectComponent(void)
	{
	}
	void GameObjectComponent::Update()
	{

	}
	void GameObjectComponent::Attach(GameObjectPtr pObject)
	{
		m_pObject = pObject;
	}
	const std::string& GameObjectComponent::GetName()
	{
		return m_name;
	}
}

