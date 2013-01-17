#pragma once

#include "core\ExtPackage.h"

namespace ld3d
{
	class DTPackage : public ExtPackage
	{
	public:
		DTPackage(CoreApiPtr pCore);
		virtual ~DTPackage(void);

		

		const wchar_t*						GetPackageName();
		int									GetClassCount();
		ComponentClass*						GetClassByIndex(int index);

		void								Release();
		CoreApiPtr							GetCoreApi();
	private:
		static GameObjectComponentPtr		Create_DT_SelectionBox(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_DT_Gizmo(GameObjectManagerPtr pManager);
	private:

		CoreApiPtr							m_pCore;
		std::vector<ComponentClass>			m_classes;
	};
}
