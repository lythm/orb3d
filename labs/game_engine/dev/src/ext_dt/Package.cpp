#include "GameEditor_ext_pch.h"

#include "Package.h"
#include "ext_dt\DT_SelectionBox.h"
#include "ext_dt\DT_Gizmo.h"


EXPORT_C_API ld3d::ExtPackage* CreatePackage(ld3d::CoreApiPtr pCore)
{
	return new ld3d::DTPackage(pCore);
}


EXPORT_C_API void DestroyPackage(ld3d::ExtPackage* pPackage)
{
	delete (ld3d::DTPackage*)pPackage;
}


namespace ld3d
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
	const wchar_t* DTPackage::GetPackageName()
	{
		return L"Design Time";
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
	void DTPackage::Release()
	{
		m_classes.clear();

	}
}
