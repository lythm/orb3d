// ObjectPropertyGrid.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "ObjectPropertyGrid.h"
#include "TransformProperty.h"
#include "AppContext.h"


// CObjectPropertyGrid

IMPLEMENT_DYNAMIC(CObjectPropertyGrid, CMFCPropertyGridCtrl)

CObjectPropertyGrid::CObjectPropertyGrid()
{

}

CObjectPropertyGrid::~CObjectPropertyGrid()
{
}


BEGIN_MESSAGE_MAP(CObjectPropertyGrid, CMFCPropertyGridCtrl)
END_MESSAGE_MAP()



// CObjectPropertyGrid 消息处理程序

CMFCPropertyGridProperty* CObjectPropertyGrid::CreateProperty(engine::Property* p)
{
	using namespace engine;
	using namespace custom_property;

	CMFCPropertyGridProperty* pProp = NULL;
	switch(p->getType())
	{
	case property_type_matrix44:
		{
			TransformProperty* pTMProp  = new TransformProperty(p->getName().c_str(), p);

			pProp = pTMProp;
		}
		break;
	case property_type_string:
		{
			std::wstring v = ((StringProperty*)p)->Get();

			pProp = new CMFCPropertyGridProperty(p->getName().c_str(), COleVariant(v.c_str()), _T("."), (DWORD_PTR)p);

			if(((StringProperty*)p)->IsReadOnly())
			{
				pProp->AllowEdit(false);
			}
		}
		break;
	case property_type_bool:
		{
			
			bool v = ((BoolProperty*)p)->Get();

			pProp = new CMFCPropertyGridProperty(p->getName().c_str(), _variant_t(v), _T("."), (DWORD_PTR)p);

			if(((BoolProperty*)p)->IsReadOnly())
			{
				pProp->AllowEdit(false);
			}
		}
		break;
	case property_type_int:
		{
			int v = ((IntProperty*)p)->Get();

			pProp = new CMFCPropertyGridProperty(p->getName().c_str(), _variant_t(v), _T("."), (DWORD_PTR)p);

			if(((IntProperty*)p)->IsReadOnly())
			{
				pProp->AllowEdit(false);
			}
		}
		break;
	default:
		{
			pProp = new CMFCPropertyGridProperty(p->getName().c_str());
		}
		break;
	}


	return pProp;
}
void CObjectPropertyGrid::UpdateGameObjectProp(engine::GameObjectPtr pObj)
{
	//return;
	m_pObj = pObj;

	RemoveAll();

	if(pObj == nullptr)
	{
		Invalidate();
		
		return;
	}

	using namespace engine;
	using namespace object_component;

	PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(pObj->GetComponent(L"PropertyManager"));
	
	for(int i = 0; i < pPM->GetPropertySetCount(); ++i)
	{
		PropertySetPtr pO = pPM->GetPropertySet(i);

		CMFCPropertyGridProperty* pCommon = new CMFCPropertyGridProperty(pO->getName().c_str());

		for(size_t ii = 0; ii < pO->getPropertyCount(); ++ii)
		{
			Property* p = pO->getProperty(ii);

			CMFCPropertyGridProperty* pSub = CreateProperty(p);

			pCommon->AddSubItem(pSub);
		}

		AddProperty(pCommon);

	}

	Invalidate();
}



void CObjectPropertyGrid::OnPropertyChanged(CMFCPropertyGridProperty* pProp) const
{
	// TODO: 在此添加专用代码和/或调用基类

	std::wstring oldname = m_pObj->GetName();

	using namespace engine;
	Property* p = (Property*)pProp->GetData();

	switch(p->getType())
	{
	case property_type_string:
		{
			((StringProperty*)p)->Set(pProp->GetValue().bstrVal);
		}
		break;
	case property_type_bool:
		{
			((BoolProperty*)p)->Set(pProp->GetValue().boolVal);

		}
		break;
	case property_type_matrix44:
		{
			custom_property::TransformProperty* pTMProp = (custom_property::TransformProperty*)p->getData();
			pTMProp->Update();
		}
		break;
	case property_type_int:
		{
			((IntProperty*)p)->Set(pProp->GetValue().intVal);
		}
		break;
	default:
		break;
	}
	
	if(oldname != m_pObj->GetName())
	{
		AppContext::UpdateObjectView();
	}

	return CMFCPropertyGridCtrl::OnPropertyChanged(pProp);
}
