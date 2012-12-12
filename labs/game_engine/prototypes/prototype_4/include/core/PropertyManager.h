#pragma once

#include "core\GameObjectComponent.h"

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
			template<typename T>
			bool								RegisterProperty(const wchar_t* szName, T* value)
			{
				return m_pCurrentOwner->registerProperty(szName, value);
			}

			void								End();

			bool								OnAttach();
			void								OnDetach();


			int									GetPropertySetCount();
			PropertySetPtr						GetPropertySet(int index);

		private:
			std::vector<PropertySetPtr>			m_PropSets;

			PropertySetPtr						m_pCurrentOwner;
		};


	}
}