#include "core_ext_pch.h"
#include "..\..\include\core\ext\PropertyManager.h"
#include "core\GameObject.h"
#include "CorePackage.h"

namespace ld3d
{
	PropertyManager::PropertyManager(GameObjectManagerPtr pManager) : GameObjectComponent(L"PropertyManager", pManager)
	{
		m_pCurrentOwner = PropertySetPtr();
	}


	PropertyManager::~PropertyManager(void)
	{
		m_PropSets.clear();
	}
	const Version& PropertyManager::GetVersion() const
	{
		return g_packageVersion;
	}
	PropertySetPtr PropertyManager::FindProperty(const std::wstring& name)
	{
		for(size_t i = 0; i < m_PropSets.size(); ++i)
		{
			if(m_PropSets[i]->getName() == name)
			{
				return m_PropSets[i];
			}
		}
		return PropertySetPtr();
	}
	PropertySetPtr PropertyManager::Begin(const std::wstring& name)
	{
		PropertySetPtr pSet = m_pManager->GetAllocator()->AllocObject<PropertySet>(name);

		m_PropSets.push_back(pSet);

		m_pCurrentOwner = pSet;

		return pSet;

	}
	void PropertyManager::AddProperty(boost::shared_ptr<Property> pProp)
	{
		m_pCurrentOwner->addProperty(pProp);
	}

	void PropertyManager::End()
	{
		m_pCurrentOwner = PropertySetPtr();
	}
	bool PropertyManager::OnAttach()
	{
		m_pCurrentOwner = PropertySetPtr();


		Begin(L"General");
		{

			RegisterProperty<std::wstring, GameObject>(m_pObject.get(), 
				L"Name", 
				&GameObject::GetName,
				&GameObject::SetName);

			RegisterProperty<math::Matrix44, GameObject>(m_pObject.get(),
				L"Transform", 
				&GameObject::GetLocalTransform,
				&GameObject::SetLocalTransform);
		}
		End();




		return true;
	}
	void PropertyManager::OnDetach()
	{
	}
	int PropertyManager::GetPropertySetCount()
	{
		return m_PropSets.size();
	}
	PropertySetPtr PropertyManager::GetPropertySet(int index)
	{
		return m_PropSets[index];
	}
}
