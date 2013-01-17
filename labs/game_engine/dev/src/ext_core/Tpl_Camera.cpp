#include "core_ext_pch.h"
#include "Tpl_Camera.h"
//#include "core\ext\CameraData.h"

namespace ld3d
{
	Tpl_Camera::Tpl_Camera(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Camera")
	{
	}


	Tpl_Camera::~Tpl_Camera(void)
	{
	}
	GameObjectPtr Tpl_Camera::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Camera");
		
		CameraDataPtr pMD = boost::shared_dynamic_cast<CameraData>(m_pManager->CreateComponent(L"Camera"));
	
		pObj->AddComponent(pMD);

	

		return pObj;
	}
	void Tpl_Camera::Release()
	{
	}
}