#include "StdAfx.h"
#include "TransformProperty.h"

namespace custom_property
{
	TransformProperty::TransformProperty(const CString& strName, ld3d::Property* pProp) : CMFCPropertyGridProperty(strName)
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


		m_rotation.x = m_pRotationX->GetValue().fltVal;
		m_rotation.y = m_pRotationY->GetValue().fltVal;
		m_rotation.z = m_pRotationZ->GetValue().fltVal;

		m_scale.x = abs(m_pScaleX->GetValue().fltVal);
		m_scale.y = abs(m_pScaleY->GetValue().fltVal);
		m_scale.z = abs(m_pScaleZ->GetValue().fltVal);


		UpdatePropValue();
	}
	void TransformProperty::UpdateValue()
	{
		using namespace ld3d;

		math::Matrix44 mat = ((Matrix44Property*)m_pProp)->Get();

		m_translation = mat.GetRow3(3);
		m_scale = mat.GetScale();
		m_scale.x = abs(m_scale.x);
		m_scale.y = abs(m_scale.y);
		m_scale.z = abs(m_scale.z);
		m_rotation = MatrixToEular(mat);

	}
	void TransformProperty::UpdatePropValue()
	{
		using namespace ld3d;

		//math::Matrix44 mat = math::MatrixScale(m_scale)  * EularToMatrix(m_rotation) * math::MatrixTranslation(m_translation);

		math::Matrix44 mat = EularToMatrix(m_rotation);
		mat.SetScale(m_scale);
		mat.SetTranslation(m_translation);

		((Matrix44Property*)m_pProp)->Set(mat);
	}
	math::Vector3 TransformProperty::MatrixToEular(const math::Matrix44& mat)
	{
		math::Vector3 r;
		math::Matrix44 rm = mat;

		rm.SetScale(math::Vector3(1, 1, 1));
		//rm.Transpose();

		// Assuming the angles are in radians.
		if (rm(1, 0) > 0.998)
		{ // singularity at north pole
			r.x = 0;
			r.y = atan2(rm(0, 2), rm(2, 2));
			r.z = math::MATH_PI/2;
			return r;
		}
		if (rm(1, 0) < -0.998) { // singularity at south pole
			r.x = 0;
			
			r.y = atan2(rm(0, 2),rm(2, 2));
			r.z = -math::MATH_PI/2;
			return r;
		}
		
		r.x  = atan2(-rm(1, 2),rm(1, 1));
		r.y  = atan2(-rm(2, 0), rm(0, 0));
		r.z  = asin(rm(1, 0));

		return math::Vector3(-math::R2D(r.x), -math::R2D(r.y), -math::R2D(r.z));
	}
	math::Matrix44 TransformProperty::EularToMatrix(const math::Vector3& r)
	{
		using namespace math;

		return MatrixRotationAxisY(D2R(r.y)) * MatrixRotationAxisZ(D2R(r.z)) * MatrixRotationAxisX(D2R(r.x));
		//return math::MatrixRotationRollPitchYaw(math::D2R(r.x), math::D2R(r.y), math::D2R(r.z));
	}
}

