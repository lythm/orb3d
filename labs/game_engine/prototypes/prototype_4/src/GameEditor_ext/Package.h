#pragma once

#include "core\ExtPackage.h"

namespace engine
{
	class Package : public ExtPackage
	{
	public:
		Package(CoreApiPtr pCore);
		virtual ~Package(void);

		

		std::wstring						GetPackageName();
		int									GetClassCount();
		ComponentClass*						GetClassByIndex(int index);


		static CoreApiPtr					GetCoreApi();
	private:
		static GameObjectComponentPtr		Create_DT_SelectionBox(GameObjectManagerPtr pManager);
	private:

		static CoreApiPtr					s_pCore;
		std::vector<ComponentClass>			m_classes;
	};
}
