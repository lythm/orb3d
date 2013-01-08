#include "GameEditor_ext_pch.h"

#include "Package.h"
#include "ext_dt\DT_SelectionBox.h"
#include "ext_dt\DT_Gizmo.h"


EXPORT_C_API engine::ExtPackage* CreatePackage(engine::CoreApiPtr pCore)
{
	return new engine::DTPackage(pCore);
}


EXPORT_C_API void DestroyPackage(engine::ExtPackage* pPackage)
{
	delete (engine::DTPackage*)pPackage;
}


namespace engine
{
	DTPackage::DTPackage(CoreApiPtr pCore)
	{
		m_pCore = pCore;

		m_classes.push_back(ComponentClass(L"DT_SelectionBox",
							L"DT",
							L"Selection Box",
							&DTPackage::Create_DT_SelectionBox));
		m_classes.push_back(ComponentClass(L"DT_Gizmo",
							L"DT",
							L"Gizmo",
							&DTPackage::Create_DT_Gizmo));
	}


	DTPackage::~DTPackage(void)
	{
	}

	CoreApiPtr DTPackage::GetCoreApi()
	{
		return m_pCore;
	}
	std::wstring DTPackage::GetPackageName()
	{
		return L"DT";
	}
	
	int DTPackage::GetClassCount()
	{
		return (int)m_classes.size();
	}
	DTPackage::ComponentClass* DTPackage::GetClassByIndex(int index)
	{
		return &m_classes[index];
	}
	GameObjectComponentPtr DTPackage::Create_DT_SelectionBox(GameObjectManagerPtr pManager)
	{
		return GameObjectComponentPtr(new DT_SelectionBox(pManager));
	}
	GameObjectComponentPtr DTPackage::Create_DT_Gizmo(GameObjectManagerPtr pManager)
	{
		return GameObjectComponentPtr(new DT_Gizmo(pManager));
	}
}
