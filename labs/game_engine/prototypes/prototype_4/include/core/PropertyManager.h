#pragma once

#include "core\GameObjectComponent.h"
#include "core\CoreApi.h"

namespace engine
{
	namespace object_component
	{
		class EXPORT_CLASS PropertyManager : public GameObjectComponent
		{
		public:

			PropertyManager(void);
			virtual ~PropertyManager(void);

			static PropertyManagerPtr			CreateComponent();


			void								Begin(const std::wstring& name);

			void								AddProperty(boost::shared_ptr<Property> pProp);

			void								End();

			bool								OnAttach();
			void								OnDetach();


			int									GetPropertySetCount();
			PropertySetPtr						GetPropertySet(int index);


			template<typename T>
			bool								RegisterProperty(const std::wstring& name, boost::function<void (const T&)> setter, boost::function<const T& ()> getter)
			{
				boost::shared_ptr<Property_T<T> > pProp = CoreApi::AllocObject<Property_T<T> >(name);
				pProp->setType(PropTypeId<T>::m_type);
				pProp->m_getter = getter;
				pProp->m_setter = setter;

				AddProperty(pProp);

				return true;
			}

		private:
			std::vector<PropertySetPtr>			m_PropSets;

			PropertySetPtr						m_pCurrentOwner;
		};


	}
}