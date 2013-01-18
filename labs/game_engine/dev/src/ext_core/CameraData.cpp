#include "core_ext_pch.h"
#include "..\..\include\core\ext\CameraData.h"

namespace ld3d
{
	CameraData::CameraData(GameObjectManagerPtr pManager) : GameObjectComponent(L"Camera", pManager)
	{
	}


	CameraData::~CameraData(void)
	{
	}
	const Version& CameraData::GetVersion() const
	{
		return g_packageVersion;
	}
	bool CameraData::OnAttach()
	{
		m_pCamera = m_pManager->GetAllocator()->AllocObject<Camera>();

		float aspect = float(800) / float(600);
		m_pCamera->PerspectiveFovLH(1.0f/ 4.0f * math::MATH_PI, aspect, 0.1f, 10000);
		
		m_pManager->GetRenderSystem()->AddCamera(m_pCamera);

		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));
		
		pPM->Begin(L"Camera");
		{
			pPM->RegisterProperty<int, Camera>(m_pCamera.get(),
									L"Rendering Order",
									&Camera::GetOrder,
									&Camera::SetOrder);

		}
		pPM->End();

		return true;
	}
	void CameraData::OnDetach()
	{
		m_pManager->GetRenderSystem()->RemoveCamera(m_pCamera);
		m_pCamera.reset();
	}
	bool CameraData::OnSerialize(DataStream* pStream)
	{
		int order = m_pCamera->GetOrder();
		pStream->WriteInt32(order);
		return true;
	}
	bool CameraData::OnUnSerialize(DataStream* pStream, const Version& version)
	{
		if(version != g_packageVersion)
		{
			return false;
		}
		int order = pStream->ReadInt32();
		m_pCamera->SetOrder(order);
		return true;
	}
	void CameraData::Update()
	{
		math::Matrix44 mat = m_pObject->GetWorldTransform();

		mat.Invert();

		m_pCamera->SetViewMatrix(mat);
	}
}
