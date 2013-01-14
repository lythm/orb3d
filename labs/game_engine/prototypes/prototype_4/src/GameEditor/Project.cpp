#include "StdAfx.h"
#include "Project.h"
#include <afxconv.h>
#include "Renderer.h"
#include "editor_utils.h"
#include "MainFrm.h"

engine::PoolAllocator				Project::s_Allocator;
ProjectPtr							Project::s_pInstance = ProjectPtr();
Project::Project(void)
{
	m_objNo	= 0;

}


Project::~Project(void)
{
}

bool Project::New(const _TCHAR* filename)
{
	s_Allocator.Initialize();

	if(false == InitEngine())
	{
		return false;
	}

	if(false == InitRenderer())
	{
		return false;
	}

	if(m_pCore->GetRenderSystem()->GetLightCount() == 0)
	{
		AddDefaultLight();
	}

	util_update_object_view(m_pCore->Root());

	return true;
}
bool Project::Load(const _TCHAR* filename)
{
	m_filePath = filename;

	USES_CONVERSION;

	TiXmlDocument doc;

	doc.LoadFile(W2A(filename));



	if(false == InitEngine())
	{
		return false;
	}

	if(false == InitRenderer())
	{
		return false;
	}


	if(m_pCore->GetRenderSystem()->GetLightCount() == 0)
	{
		AddDefaultLight();
	}

	util_update_object_view(m_pCore->Root());
	return true;
}
bool Project::Save(const _TCHAR* filename)
{
	TiXmlDocument doc;

	USES_CONVERSION;
	doc.InsertEndChild(TiXmlElement("Project"));

	if(false == doc.SaveFile(W2A(filename)))
	{
		return false;
	}

	m_filePath = filename;
	return true;
}
void Project::Close()
{
	if(m_pCore)
	{
		m_pCore->ResetScene();
	}

	m_pSelObject.reset();
	
	ReleaseRenderer();
	ReleaseEngine();

	m_pCore.reset();
	m_pRenderer.reset();
	m_pPathManager.reset();

	//s_Allocator.Release();
}

void Project::AddDefaultLight()
{
	using namespace engine;
	using namespace engine;

	GameObjectPtr pObj = CreateObjectFromTpl(L"Default Light", L"SkyLight");
	pObj->SetTranslation(1, 1, 1);
	pObj->LookAt(math::Vector3(0, 0, 0));

}
void Project::CreateObject_Empty()
{
	using namespace engine;
	GameObjectPtr pObj = CreateObject(L"GameObject");
}
engine::GameObjectPtr Project::CreateObject(const std::wstring& name)
{
	using namespace engine;

	CString full_name;

	full_name.Format(L"%s-%d", name.c_str(), m_objNo);

	GameObjectPtr pObj = m_pCore->CreateGameObject(full_name.GetString());

	GameObjectComponentPtr pPM = CreateGameObjectComponent(L"DT_Gizmo");
	pObj->AddComponent(pPM);

	m_objNo++;
	return pObj;
}
engine::GameObjectPtr Project::CreateObjectFromTpl(const std::wstring& name, const std::wstring& tpl)
{
	using namespace engine;

	CString full_name;

	full_name.Format(L"%s-%d", name.c_str(), m_objNo);

	GameObjectPtr pObj = m_pCore->CreatGameObjectFromTemplate(tpl, full_name.GetString());

	GameObjectComponentPtr pPM = CreateGameObjectComponent(L"DT_Gizmo");
	pObj->AddComponent(pPM);

	m_objNo++;
	return pObj;
}
bool Project::InitRenderer()
{
	m_pRenderer = RendererPtr(new Renderer);
	if(m_pRenderer->Initialize(m_pCore) == false)
	{
		return false;
	}
	return true;
}
void Project::ReleaseRenderer()
{
	if(m_pRenderer)
	{
		m_pRenderer->Release();
		m_pRenderer.reset();
	}
}

bool Project::InitEngine()
{
	using namespace engine;

	CWnd* pWnd = util_get_rendering_wnd();

	CRect rc;

	pWnd->GetClientRect(rc);

	int w = rc.Width();
	int h = rc.Height();

	m_pCore = CoreApiPtr(new CoreApi());

	GraphicsSetting setting;
	setting.sysMod = L"./d11graphics.dll";
	setting.backBufferCount = 2;
	setting.depthStencilFormat = G_FORMAT_D24_UNORM_S8_UINT;
	setting.frameBufferFormat = G_FORMAT_R8G8B8A8_UNORM;
	setting.frameBufferHeight = h;
	setting.frameBufferWidth = w;
	setting.multiSampleCount = 1;
	setting.multiSampleQuality = 0;
	setting.windowed = true;
	setting.wnd = pWnd->m_hWnd;

#ifdef _DEBUG
	if(false == m_pCore->Initialize(setting))
	{
		return false;
	}
#else
	if(false == s_pCore->Initialize(setting, &s_Allocator))
	{
		return false;
	}
#endif

	m_pCore->GetGameObjectManager()->LoadPackage(L"./extensions/ext_dt.dll");
	m_pCore->GetGameObjectManager()->LoadPackage(L"./extensions/ext_voxel.dll");

	m_pCore->GetRenderSystem()->SetClearColor(math::Color4(0.3f, 0.2f, 0.4f, 1.0f));

	return true;
}
void Project::ReleaseEngine()
{
	if(m_pCore != NULL)
	{
		m_pCore->Release();
		m_pCore.reset();
	}
}
void Project::Reset()
{
	ReleaseRenderer();
	ReleaseEngine();

	InitEngine();
	InitRenderer();
}
engine::CoreApiPtr Project::GetCoreApi()
{
	return m_pCore;
}
RendererPtr Project::GetRenderer()
{
	return m_pRenderer;
}
engine::GameObjectComponentPtr Project::CreateGameObjectComponent(const std::wstring& name)
{
	return m_pCore->CreateGameObjectComponent(name);
}
void Project::ResizeRenderer(int cx, int cy)
{
	if(m_pRenderer)
	{
		m_pRenderer->Resize(cx, cy);
	}
}
void Project::SelectObject(engine::GameObjectPtr pObj)
{
	m_pSelObject = pObj;
}
engine::GameObjectPtr Project::GetSelObject()
{
	return m_pSelObject;
}
engine::GameObjectPtr Project::Root()
{
	if(m_pCore == nullptr)
	{
		return engine::GameObjectPtr();
	}
	return m_pCore->Root();
}
void Project::HandleMessage(MSG& msg)
{
	if(m_pCore)
	{
		m_pCore->HandleMessage(msg);
	}
}
void Project::Render()
{
	if(m_pRenderer)
	{
		m_pRenderer->Render();
	}
}
bool Project::ShowingGrid()
{
	return m_pRenderer->ShowingGrid();
}
void Project::ShowGrid(bool bShow)
{
	m_pRenderer->ShowGrid(bShow);
}
ProjectPtr Project::Instance()
{
	if(s_pInstance == nullptr)
	{
		s_pInstance = ProjectPtr(new Project);
	}

	return s_pInstance;
}

