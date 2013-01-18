#include "core_pch.h"
#include "..\..\include\core\GameObjectComponent.h"
#include "core_utils.h"
#include "core\DataStream.h"

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
		const Version& v = GetVersion();
		pStream->WriteInt32(v.AsUInt32());

		return OnSerialize(pStream);
	}
	bool GameObjectComponent::UnSerialize(DataStream* pStream)
	{
		uint32 v = pStream->ReadInt32();

		return OnUnSerialize(pStream, Version(v));
	}
	bool GameObjectComponent::OnSerialize(DataStream* pStream)
	{
		return true;
	}
	bool GameObjectComponent::OnUnSerialize(DataStream* pStream, const Version& version)
	{
		return true;
	}
	GameObjectComponentPtr GameObjectComponent::Clone()
	{
		//GameObjectComponentPtr pClone = alloc_object<GameObjectComponent, GameObjectManagerPtr>(m_pManager);

		//pClone->SetName(GetName());

		return GameObjectComponentPtr();
	}
	const wchar_t* GameObjectComponent::GetVersionString()
	{
		return GetVersion().AsWString().c_str();
	}
	const std::vector<std::wstring>& GameObjectComponent::GetDependences()
	{
		static std::vector<std::wstring> deps;

		return deps;
	}
	bool GameObjectComponent::IsExclusive()
	{
		return true;
	}
}

