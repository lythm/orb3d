#include "StdAfx.h"
#include "TransformProperty.h"

namespace custom_property
{
	TransformProperty::TransformProperty(const CString& strName, engine::Property* pProp) : CMFCPropertyGridProperty(strName)
	{
		m_pProp = pProp;

		m_pProp->setData(this);


		UpdateValue();


		CMFCPropertyGridProperty* pTrans = new CMFCPropertyGridProperty(L"Translation");

		m_pTransX = new CMFCPropertyGridProperty(L"X", COleVariant(m_translation.x), L"", (DWORD_PTR)m_pProp);
		m_pTransY = new CMFCPropertyGridProperty(L"Y", COleVariant(m_translation.y), L"", (DWORD_PTR)m_pProp);
		m_pTransZ = new CMFCPropertyGridProperty(L"Z", COleVariant(m_translation.z), L"", (DWORD_PTR)m_pProp);

		pTrans->AddSubItem(m_pTransX);
		pTrans->AddSubItem(m_pTransY);
		pTrans->AddSubItem(m_pTransZ);


		AddSubItem(pTrans);

		CMFCPropertyGridProperty* pRotation = new CMFCPropertyGridProperty(L"Rotation");

		m_pRotationX = new CMFCPropertyGridProperty(L"X", COleVariant(m_rotation.x), L"", (DWORD_PTR)m_pProp);
		m_pRotationY = new CMFCPropertyGridProperty(L"Y", COleVariant(m_rotation.y), L"", (DWORD_PTR)m_pProp);
		m_pRotationZ = new CMFCPropertyGridProperty(L"Z", COleVariant(m_rotation.z), L"", (DWORD_PTR)m_pProp);

		pRotation->AddSubItem(m_pRotationX);
		pRotation->AddSubItem(m_pRotationY);
		pRotation->AddSubItem(m_pRotationZ);

		AddSubItem(pRotation);

		CMFCPropertyGridProperty* pScale = new CMFCPropertyGridProperty(L"Scale");

		m_pScaleX = new CMFCPropertyGridProperty(L"X", COleVariant(m_scale.x), L"", (DWORD_PTR)m_pProp);
		m_pScaleY = new CMFCPropertyGridProperty(L"Y", COleVariant(m_scale.y), L"", (DWORD_PTR)m_pProp);
		m_pScaleZ = new CMFCPropertyGridProperty(L"Z", COleVariant(m_scale.z), L"", (DWORD_PTR)m_pProp);

		pScale->AddSubItem(m_pScaleX);
		pScale->AddSubItem(m_pScaleY);
		pScale->AddSubItem(m_pScaleZ);

		AddSubItem(pScale);
	}


	TransformProperty::~TransformProperty(void)
	{
		m_pProp->setData(nullptr);
	}
	void TransformProperty::Update()
	{
		m_translation.x = m_pTransX->GetValue().fltVal;
		m_translation.y = m_pTransY->GetValue().fltVal;
		m_translation.z = m_pTransZ->GetValue().fltVal;

		m_scale.x = m_pScaleX->GetValue().fltVal;
		m_scale.y = m_pScaleY->GetValue().fltVal;
		m_scale.z = m_pScaleZ->GetValue().fltVal;

		UpdatePropValue();

		
	}
	void TransformProperty::UpdateValue()
	{
		using namespace engine;
		
		math::Matrix44 mat = ((Property_T<math::Matrix44>*)m_pProp)->m_getter();

		m_translation = mat.GetRow3(3);
		m_scale = mat.GetScale();

	}
	void TransformProperty::UpdatePropValue()
	{
		using namespace engine;
		
		math::Matrix44 mat = ((Property_T<math::Matrix44>*)m_pProp)->m_getter();

		mat.SetTranslation(m_translation);

		mat.SetScale(m_scale);

		((Property_T<math::Matrix44>*)m_pProp)->m_setter(mat);

	}
}

