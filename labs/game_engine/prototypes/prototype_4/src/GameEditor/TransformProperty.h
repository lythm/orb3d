#pragma once

namespace custom_property
{
	class TransformProperty: public CMFCPropertyGridProperty
	{
	public:
		TransformProperty(const CString& strName, engine::Property* pVal);
		virtual ~TransformProperty(void);

		void								Update();


	private:
		void								UpdateValue();
		void								UpdatePropValue();
	private:

		math::Vector3						m_translation;
		math::Vector3						m_scale;
		math::Vector3						m_rotation;

		engine::Property*					m_pProp;


		CMFCPropertyGridProperty*			m_pTransX;
		CMFCPropertyGridProperty*			m_pTransY;
		CMFCPropertyGridProperty*			m_pTransZ;

		CMFCPropertyGridProperty*			m_pRotationX;
		CMFCPropertyGridProperty*			m_pRotationY;
		CMFCPropertyGridProperty*			m_pRotationZ;

		CMFCPropertyGridProperty*			m_pScaleX;
		CMFCPropertyGridProperty*			m_pScaleY;
		CMFCPropertyGridProperty*			m_pScaleZ;

	};

}
