#include "StdAfx.h"
#include "Project.h"
#include <afxconv.h>
#include "Renderer.h"
#include "editor_utils.h"
#include "MainFrm.h"
#include "GameScene.h"
#include "EditorCamera.h"


ld3d::PoolAllocator					g_Allocator;
ProjectPtr							Project::s_pInstance = ProjectPtr();
Project::Project(void)
{
	m_clearClr = math::Color4(0.0f, 0.2f, 0.3f, 1.0f);
}


Project::~Project(void)
{
}

bool Project::New(const _TCHAR* filename)
{
	//s_Allocator.Initialize();

	Reset();

	if(false == CreateNewProject(filename))
	{
		return false;
	}

	m_pScene = GameScenePtr(new GameScene(m_pCore));

	if(false == m_pScene->New())
	{
		return false;
	}

	return true;
}
bool Project::Load(const _TCHAR* filename)
{
	Reset();

	m_filePath = filename;

	RestoreCurrentDirectory();


	USES_CONVERSION;

	TiXmlDocument doc;

	if(false == doc.LoadFile(W2A(filename)))
	{
		return false;
	}

	TiXmlElement* root = doc.RootElement();
	if(root == nullptr)
	{
		return false;
	}

	TiXmlElement* camera = root->FirstChildElement("camera");
	if(camera)
	{
		TiXmlElement* eye = camera->FirstChildElement("eye_pos");
		if(eye)
		{
			math::Vector3 ep;
			if(eye->GetText())
			{
				sscanf_s(eye->GetText(), "%f, %f, %f", &ep.x, &ep.y, &ep.z);
			}
			m_pRenderer->GetCamera()->SetEyePos(ep);
		}
		
		TiXmlElement* focus = camera->FirstChildElement("focus_pos");
		if(focus)
		{
			math::Vector3 fp;
			if(focus->GetText())
			{
				sscanf_s(focus->GetText(), "%f, %f, %f", &fp.x, &fp.y, &fp.z);
			}
		
			m_pRenderer->GetCamera()->SetFocusPos(fp);
		}
	}


	TiXmlElement* scene = root->FirstChildElement("scene");
	
	m_pScene = GameScenePtr(new GameScene(m_pCore));

	if(scene == nullptr || scene->GetText() == nullptr || scene->GetText() == "")
	{
		if(false == m_pScene->New())
		{
			return false;
		}
	}
	else
	{
		if(false == m_pScene->Load(scene->GetText()))
		{
			return false;
		}
	}
	
	return true;
}
bool Project::Save(const _TCHAR* filename)
{
	
	TiXmlDocument doc;

	USES_CONVERSION;
	TiXmlNode* pRoot = doc.InsertEndChild(TiXmlElement("project"));

	TiXmlElement scene("scene");

	if(m_pScene)
	{
		scene.InsertEndChild(TiXmlText(m_pScene->GetFileName().string().c_str()));
	}
	pRoot->InsertEndChild(scene);
	
	TiXmlElement clearClr("clear_color");

	char szBuffer[1024];

	sprintf_s(szBuffer,1024, "%.3f,%.3f,%.3f,%.3f", m_clearClr.r, m_clearClr.g, m_clearClr.b, m_clearClr.a);

	clearClr.InsertEndChild(TiXmlText(szBuffer));

	pRoot->InsertEndChild(clearClr);

	TiXmlElement camera("camera");

	math::Vector3 eye = m_pRenderer->GetCamera()->GetEyePos();
	math::Vector3 focus = m_pRenderer->GetCamera()->GetFocusPos();

	
	TiXmlElement eEye("eye_pos");
	sprintf_s(szBuffer,1024, "%.3f,%.3f,%.3f", eye.z, eye.y, eye.z);
	eEye.InsertEndChild(TiXmlText(szBuffer));

	TiXmlElement eFocus("focus_pos");
	sprintf_s(szBuffer,1024, "%.3f,%.3f,%.3f", focus.z, focus.y, focus.z);
	eFocus.InsertEndChild(TiXmlText(szBuffer));

	camera.InsertEndChild(eEye);
	camera.InsertEndChild(eFocus);

	pRoot->InsertEndChild(camera);

	if(false == doc.SaveFile(W2A(filename)))
	{
		return false;
	}

	m_filePath = filename;

	RestoreCurrentDirectory();

	return true;
}
bool Project::Save()
{
	return Save(m_filePath.wstring().c_str());
}
void Project::Close()
{
	if(m_pScene)
	{
		m_pScene->Close();
	}
	
	m_pSelObject.reset();

	ReleaseRenderer();
	ReleaseEngine();

	m_pCore.reset();
	m_pRenderer.reset();
	m_pPathManager.reset();

}

void Project::CreateObject_Empty()
{
	m_pScene->CreateObject_Empty();
}
ld3d::GameObjectPtr Project::CreateObject(const std::wstring& name)
{
	return m_pScene->CreateObject(name);
}
ld3d::GameObjectPtr Project::CreateObjectFromTpl(const std::wstring& name, const std::wstring& tpl)
{
	return m_pScene->CreateObjectFromTpl(name, tpl);
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
	using namespace ld3d;

	CWnd* pWnd = util_get_rendering_wnd();

	CRect rc;

	pWnd->GetClientRect(rc);

	int w = rc.Width();
	int h = rc.Height();

	m_pCore = CoreApiPtr(new CoreApi());

	CoreApi::SetLogger(util_log_info);


	SysSetting setting;
	setting.graphics.sysMod = L"./d11graphics.dll";
	setting.graphics.backBufferCount = 2;
	setting.graphics.depthStencilFormat = G_FORMAT_D24_UNORM_S8_UINT;
	setting.graphics.frameBufferFormat = G_FORMAT_R8G8B8A8_UNORM;
	setting.graphics.frameBufferHeight = h;
	setting.graphics.frameBufferWidth = w;
	setting.graphics.multiSampleCount = 1;
	setting.graphics.multiSampleQuality = 0;
	setting.graphics.windowed = true;
	setting.graphics.wnd = pWnd->m_hWnd;

	setting.input.sysMod = L"";
	setting.input.wnd = pWnd->m_hWnd;

	setting.sound.maxChannels = 100;
	setting.sound.sysMod = L"./fmod_sound.dll";

	setting.physics.sysMod = L"";


#ifdef _DEBUG
	if(false == m_pCore->Initialize(setting))
	{
		return false;
	}
#else
	if(false == s_pCore->Initialize(setting, &g_Allocator))
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
	Close();

	InitEngine();
	InitRenderer();
}
ld3d::CoreApiPtr Project::GetCoreApi()
{
	return m_pCore;
}
RendererPtr Project::GetRenderer()
{
	return m_pRenderer;
}
ld3d::GameObjectComponentPtr Project::CreateGameObjectComponent(const std::wstring& name)
{
	return m_pScene->CreateGameObjectComponent(name);
}
void Project::ResizeRenderer(int cx, int cy)
{
	if(m_pRenderer)
	{
		m_pRenderer->Resize(cx, cy);
	}
}
void Project::SelectObject(ld3d::GameObjectPtr pObj)
{
	m_pSelObject = pObj;
}
ld3d::GameObjectPtr Project::GetSelObject()
{
	return m_pSelObject;
}
ld3d::GameObjectPtr Project::Root()
{
	if(m_pScene == nullptr)
	{
		return ld3d::GameObjectPtr();
	}
	return m_pScene->Root();
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
void Project::RenderPreview()
{
	m_pRenderer->RenderPreview();
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

bool Project::CreateNewProject(const CString& dir)
{
	using namespace boost;
	using namespace filesystem;

	path p(dir.GetString());

	if(p.has_extension() == false)
	{
		p += path(L".gp");
	}
	path tar = p.parent_path();

	path init = initial_path();

	if(false == util_cpoy_directory(init / path(L"assets"), tar / path(L"assets")))
	{
		return false;
	}

	if(false == create_directory(tar / path(L"temp")))
	{
		return false;
	}

	if(false == create_directory(tar / path(L"packages")))
	{
		return false;
	}

	Save(dir);

	RestoreCurrentDirectory();
	return true;
}
void Project::RestoreCurrentDirectory()
{
	SetCurrentDirectory(GetProjectRootPath().wstring().c_str());
}

void Project::SetClearColor(const math::Color4& clr)
{
	m_clearClr = clr;

	m_pRenderer->SetClearColor(m_clearClr);
}
const math::Color4 Project::GetClearColor()
{
	return m_clearClr;
}
boost::filesystem::path	Project::GetProjectRootPath()
{
	return m_filePath.parent_path();
}
boost::filesystem::path	Project::GetProjectFile()
{
	return m_filePath;
}
bool Project::SaveScene(const _TCHAR* filename)
{
	using namespace boost::filesystem;

	path r = GetRelativePath(path(filename));
	RestoreCurrentDirectory();
	return m_pScene->Save(r);
}
bool Project::LoadScene(const _TCHAR* filename)
{

	using namespace boost::filesystem;

	path r = GetRelativePath(path(filename));

	RestoreCurrentDirectory();
	return m_pScene->Load(r);
}
boost::filesystem::path	Project::GetGameSceneFile()
{
	return m_pScene->GetFileName();
}
void Project::CloseScene()
{
	m_pScene->Close();
}
bool Project::NewScene()
{
	return m_pScene->New();
}
boost::filesystem::path	Project::GetRelativePath(boost::filesystem::path p)
{
	using namespace boost::filesystem;

	path r = util_get_relative_path(p, GetProjectRootPath());

	return r;
}
