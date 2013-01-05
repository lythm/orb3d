#include "GameEditor_ext_pch.h"

#include "Package.h"
#include "DT_SelectionBox.h"
#include "dt_ext\DT_Gizmo.h"


EXPORT_C_API engine::ExtPackage* CreatePackage(engine::CoreApiPtr pCore)
{
	return new engine::Package(pCore);
}


EXPORT_C_API void DestroyPackage(engine::ExtPackage* pPackage)
{
	delete (engine::Package*)pPackage;
}


namespace engine
{
	CoreApiPtr					Package::s_pCore;

	Package::Package(CoreApiPtr pCore)
	{
		m_classes.push_back(ComponentClass(L"DT_SelectionBox",
							L"DT",
							L"Selection Box",
							&Package::Create_DT_SelectionBox));
		m_classes.push_back(ComponentClass(L"DT_Gizmo",
							L"DT",
							L"Gizmo",
							&Package::Create_DT_Gizmo));
	}


	Package::~Package(void)
	{
	}

	CoreApiPtr Package::GetCoreApi()
	{
		return s_pCore;
	}
	std::wstring Package::GetPackageName()
	{
		return L"core_ext_package";
	}
	
	int Package::GetClassCount()
	{
		return (int)m_classes.size();
	}
	Package::ComponentClass* Package::GetClassByIndex(int index)
	{
		return &m_classes[index];
	}
	GameObjectComponentPtr Package::Create_DT_SelectionBox(GameObjectManagerPtr pManager)
	{
		return GameObjectComponentPtr(new DT_SelectionBox(pManager));
	}
	GameObjectComponentPtr Package::Create_DT_Gizmo(GameObjectManagerPtr pManager)
	{
		return GameObjectComponentPtr(new DT_Gizmo(pManager));
	}
}
