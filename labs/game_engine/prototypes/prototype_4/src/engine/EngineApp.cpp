#include "pch.h"
#include "EngineApp.h"

#include <tchar.h>

namespace engine
{

	class ACom : public GameObjectComponent
	{
	public:
		ACom()
		{
			m_name = "ACom";
		}
		virtual ~ACom()
		{
			OutputDebugStringA("ACom deleted\n");
		}

		void Update()
		{
			OutputDebugStringA(m_name.c_str());
			OutputDebugStringA("\n");
		}
	};

	class BCom : public GameObjectComponent
	{
	public:
		BCom()
		{
			m_name = "BCom";
		}
		virtual ~BCom()
		{
			OutputDebugStringA("BCom deleted\n");
		}

		void Update()
		{
			OutputDebugStringA(m_name.c_str());
			OutputDebugStringA("\n");
		}
	};

	EngineApp::EngineApp(void)
	{
	}


	EngineApp::~EngineApp(void)
	{
	}
	void EngineApp::OnUpdate()
	{
		m_pObjectManager->UpdateObjects();


	}
	bool EngineApp::OnInit()
	{
		m_pObjectManager = GameObjectManagerPtr(new engine::GameObjectManager);

		GameObjectPtr pRoot = m_pObjectManager->GetRoot();

		GameObjectPtr pObj = GameObjectPtr(new GameObject());

		pObj->AddComponent(boost::shared_ptr<ACom>(new ACom()));

		pObj->AddComponent(boost::shared_ptr<BCom>(new BCom()));
		
		pObj->LinkTo(pRoot);

		return true;
	}
	void EngineApp::OnRelease()
	{
		m_pObjectManager->ReleaseAllObject();
		m_pObjectManager.reset();
		
	}

}






int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	using namespace engine;
	EngineApp app;

	if(false == app.Initialize(hInstance, L"Main Window", 800, 600))
	{
		return -1;
	}
	app.Run();

	app.Release();

	return 0;
}
