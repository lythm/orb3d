#include "core_pch.h"
#include "..\..\include\core\GameObjectComponent.h"
#include "core_utils.h"

namespace ld3d
{
	GameObjectComponent::GameObjectComponent(const std::wstring& name, GameObjectManagerPtr pManager)
	{
		SetName(name);	
		m_pManager = pManager;
	}
	GameObjectComponent::GameObjectComponent(GameObjectManagerPtr pManager)
	{
		m_pManager = pManager;
	}

	GameObjectComponent::~GameObjectComponent(void)
	{
		m_pObject.reset();
		m_name = L"";
	}
	void GameObjectComponent::Update()
	{

	}
	bool GameObjectComponent::Attach(GameObjectPtr pObject)
	{
		m_pObject = pObject;

		return OnAttach();
	}
	void GameObjectComponent::Detach()
	{
		OnDetach();
		m_pObject.reset();
		m_pManager.reset();
	}
	const std::wstring& GameObjectComponent::GetName()
	{
		return m_name;
	}
	bool GameObjectComponent::OnAttach()
	{
		return true;
	}
	void GameObjectComponent::OnDetach()
	{
	}
	void GameObjectComponent::SetName(const std::wstring& name)
	{
		m_name = name;
	}
	GameObjectPtr GameObjectComponent::GetGameObject()
	{
		return m_pObject;
	}
	
	bool GameObjectComponent::Serialize(DataStream* pStream)
	{
		
		return true;
	}
	bool GameObjectComponent::UnSerialize(DataStream* pStream)
	{
		return true;

	}
	
	GameObjectComponentPtr GameObjectComponent::Clone()
	{
		GameObjectComponentPtr pClone = alloc_object<GameObjectComponent, GameObjectManagerPtr>(m_pManager);

		pClone->SetName(GetName());

		return pClone;
	}
}

