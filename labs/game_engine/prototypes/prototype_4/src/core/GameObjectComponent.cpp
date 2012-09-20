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
		m_name = L"";
	}
	void GameObjectComponent::Update()
	{
		
	}
	void GameObjectComponent::Attach(GameObjectPtr pObject)
	{
		m_pObject = pObject;

		OnAttach();
	}
	void GameObjectComponent::Detach()
	{
		OnDetach();
		m_pObject.reset();
	}
	const std::wstring& GameObjectComponent::GetName()
	{
		return m_name;
	}
	void GameObjectComponent::OnAttach()
	{
	}
	void GameObjectComponent::OnDetach()
	{
	}
	void GameObjectComponent::SetName(const std::wstring& name)
	{
		m_name = name;
	}
}

