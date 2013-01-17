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

		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));
		
		pPM->Begin(L"Camera");
		{
			

		}
		pPM->End();

		return true;
	}
	void CameraData::OnDetach()
	{
		m_pCamera.reset();
	}
	bool CameraData::OnSerialize(DataStream* pStream)
	{
		return true;
	}
	bool CameraData::OnUnSerialize(DataStream* pStream, const Version& version)
	{
		return true;
	}
	void CameraData::Update()
	{
	}
}
