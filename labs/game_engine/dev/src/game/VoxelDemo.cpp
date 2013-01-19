#include "game_pch.h"
#include "VoxelDemo.h"

#include <windowsx.h>

VoxelDemo::VoxelDemo(void)
{
}


VoxelDemo::~VoxelDemo(void)
{
}
bool VoxelDemo::Init(ld3d::CoreApiPtr pCore)
{
	using namespace ld3d;

	m_pCore = pCore;

	//m_pSound = m_pCore->GetSysSound()->CreateSound("./assets/standard/music/1.mp3");

	//m_pChannel = m_pCore->GetSysSound()->AllocChannel(m_pSound);

	m_pChannel = m_pCore->GetSysSound()->Create3DStream("./assets/standard/music/1.mp3");
	
	//m_pChannel = m_pCore->GetSysSound()->Create3DStream("http://music.k618.cn/tytq/song/201208/W020120827815517810655.mp3");

	
	m_pChannel->Play(true);
	
	m_pCore->AddEventHandler(EV_WINMSG, boost::bind(&VoxelDemo::OnMsg, this, _1));

	m_pCore->LoadPackage(L"./extensions/ext_voxel.dll");

	m_pCore->GetRenderSystem()->SetGlobalAmbient(math::Color4(0, 0.1, 0.2, 1.0));
	m_pCore->GetRenderSystem()->SetClearColor(math::Color4(0.3, 0.2, 0.3, 1));

	m_pCamera = m_pCore->GetAllocator()->AllocObject<ld3d::Camera>();
	m_pCamera->PerspectiveFovLH(0.25 * 3.14, 4.0 / 3.0, 0.01, 10000);
	m_pCamera->LookAtLH(math::Vector3(2, 2, 2), math::Vector3(0, 0, 0), math::Vector3(0, 1, 0));

	m_pCore->AddCamera(m_pCamera);

	m_pCore->CreatGameObjectFromTemplate(L"Plane", L"Plane");


	GameObjectPtr pCube = m_pCore->CreatGameObjectFromTemplate(L"Cube", L"Cube");
	pCube->Translate(0, 0.5, 0);
	GameObjectPtr pLight = m_pCore->CreatGameObjectFromTemplate(L"SkyLight", L"light");

	pLight->SetTranslation(10, 10, 10);
	pLight->LookAt(pCube);
	return true;
}
void VoxelDemo::Release()
{
}
void VoxelDemo::Update()
{
	m_pCore->Render(m_pCamera);
	m_pCore->ClearRenderQueue();

	m_pCore->Present();
}
void VoxelDemo::OnMsg(ld3d::EventPtr pEvent)
{
	using namespace ld3d;
	using namespace math;

	boost::shared_ptr<Event_WindowMessage> pMsg = boost::shared_dynamic_cast<Event_WindowMessage>(pEvent);

	switch(pMsg->msg.message)
	{
	case WM_MOUSEMOVE:
		{
			int x =  GET_X_LPARAM(pMsg->msg.lParam);
			int y =  GET_Y_LPARAM(pMsg->msg.lParam); ;
			static int lastx = x;
			static int lasty = y;

			int dx = x - lastx;
			int dy = y - lasty;

			if(pMsg->msg.wParam & MK_LBUTTON)
			{
				Matrix44 view = m_pCamera->GetViewMatrix();
				Vector3 axis_x = m_pCamera->GetAxisX();

				m_pCamera->SetViewMatrix(MatrixRotationAxisY(-dx * 0.01) * MatrixRotationAxis(-axis_x, dy * 0.01) * view);
			}

			lastx = x;
			lasty = y;
		}
		break;

	case WM_MOUSEWHEEL:
		{
			int zDelta = -GET_WHEEL_DELTA_WPARAM(pMsg->msg.wParam);

			using namespace math;

			Matrix44 view = m_pCamera->GetViewMatrix();
			Vector3 axis_z = m_pCamera->GetAxisZ();

			m_pCamera->SetViewMatrix( MatrixTranslation(0.01 * zDelta * axis_z) * view);

			view = m_pCamera->GetViewMatrix();
			math::Vector3 eye(0, 0, 0);
			math::Vector3 up = m_pCamera->GetAxisY();
			math::Vector3 forward = m_pCamera->GetAxisZ();
			
			view.Invert();
			math::TransformCoord(eye, view);

			m_pCore->GetSysSound()->SetListenerAttr(eye, math::Vector3(), forward, up);

		}
		break;

	default:
		break;
	}
}
