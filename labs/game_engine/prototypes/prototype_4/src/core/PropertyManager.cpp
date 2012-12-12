#include "core_pch.h"
#include "..\..\include\core\PropertyManager.h"
#include "core_utils.h"
#include "core\GameObject.h"

namespace engine
{
	namespace object_component
	{
		PropertyManagerPtr PropertyManager::CreateComponent()
		{
			return alloc_object<PropertyManager>();
		}
		PropertyManager::PropertyManager(void) : GameObjectComponent(L"PropertyManager")
		{
			m_pCurrentOwner = PropertySetPtr();
		}


		PropertyManager::~PropertyManager(void)
		{
			m_PropSets.clear();
		}
		void PropertyManager::Begin(const std::wstring& name)
		{
			PropertySetPtr pSet = alloc_object<PropertySet>(name);

			m_PropSets.push_back(pSet);

			m_pCurrentOwner = pSet;
			
		}
		
		void PropertyManager::End()
		{
			m_pCurrentOwner = PropertySetPtr();
		}
		bool PropertyManager::OnAttach()
		{
			m_pCurrentOwner = PropertySetPtr();


			Begin(L"General");

			RegisterProperty(L"Name", m_pObject->GetNamePtr());
		
			
			RegisterProperty(L"Transform", m_pObject->GetLocalTransformPtr());
			
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
}
