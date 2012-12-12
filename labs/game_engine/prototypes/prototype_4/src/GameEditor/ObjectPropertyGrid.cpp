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
	case type_matrix44:
		{
			TransformProperty* pTMProp  = new TransformProperty(p->getName().c_str(), p);

			pProp = pTMProp;
		}
		break;
	case Property::type_string:
		{
			pProp = new CMFCPropertyGridProperty(p->getName().c_str(), COleVariant(p->getVal<std::wstring>().c_str()), _T("."), (DWORD_PTR)p);
		}
		break;
	case Property::type_bool:
		{
			
			pProp = new CMFCPropertyGridProperty(p->getName().c_str(), _variant_t(p->getVal<bool>()), _T("."), (DWORD_PTR)p);
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

	using namespace engine;
	Property* p = (Property*)pProp->GetData();

	switch(p->getType())
	{
	case Property::type_string:
		{
			p->setVal<std::wstring>((wchar_t*)(pProp->GetValue().bstrVal));
		}
		break;
	case Property::type_bool:
		{
			p->setVal<bool>(pProp->GetValue().boolVal);
		}
		break;
	case type_matrix44:
		{
			custom_property::TransformProperty* pTMProp = (custom_property::TransformProperty*)p->getData();
			pTMProp->Update();
		}
		break;
	default:
		break;
	}
	
	AppContext::UpdateObjectView();


	return CMFCPropertyGridCtrl::OnPropertyChanged(pProp);
}
