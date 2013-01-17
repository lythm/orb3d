#pragma once

#include "core\GameObjectComponent.h"
#include "core\allocator.h"
#include "core\coreapi.h"

namespace ld3d
{

	class EXPORT_CLASS PropertyManager : public GameObjectComponent
	{
	public:

		PropertyManager(GameObjectManagerPtr pManager);
		virtual ~PropertyManager(void);

		PropertySetPtr						Begin(const std::wstring& name);
		PropertySetPtr						FindProperty(const std::wstring& name);
		void								AddProperty(boost::shared_ptr<Property> pProp);
		void								End();

		bool								OnAttach();
		void								OnDetach();
		const Version&						GetVersion() const;

		int									GetPropertySetCount();
		PropertySetPtr						GetPropertySet(int index);


		template<typename T>
		bool								RegisterProperty(const std::wstring& name, 
			boost::function<const T& ()> getter,
			boost::function<void (const T&)> setter = boost::function<void (const T&)>())
		{
			boost::shared_ptr<Property_T<T> > pProp = CoreApi::GetAllocator()->AllocObject<Property_T<T> >(name);
			pProp->setType(PropTypeId<T>::m_type);
			pProp->m_getter = getter;
			pProp->m_setter = setter;

			AddProperty(pProp);

			return true;
		}

		template<typename T, typename TObject>
		bool								RegisterProperty(TObject* pObj, 
			const std::wstring& name, 
			boost::function<const T& (TObject*)> getter,
			boost::function<void (TObject*, const T&)> setter =  boost::function<void (TObject*, const T&)>())
		{
			boost::shared_ptr<Property_T<T> > pProp = CoreApi::GetAllocator()->AllocObject<Property_T<T> >(name);
			pProp->setType(PropTypeId<T>::m_type);
			pProp->m_getter = boost::bind(getter, pObj);

			if(setter.empty() == false)
			{
				pProp->m_setter = boost::bind(setter, pObj, _1);
			}
			else
			{
				pProp->m_setter.clear();
			}

			AddProperty(pProp);

			return true;
		}

	private:
		std::vector<PropertySetPtr>			m_PropSets;

		PropertySetPtr						m_pCurrentOwner;
	};
}
