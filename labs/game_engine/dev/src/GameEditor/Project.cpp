#include "StdAfx.h"
#include "Project.h"
#include <afxconv.h>
#include "Renderer.h"
#include "editor_utils.h"
#include "MainFrm.h"
#include "GameScene.h"

engine::PoolAllocator				Project::s_Allocator;
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

	USES_CONVERSION;

	TiXmlDocument doc;

	doc.LoadFile(W2A(filename));

	TiXmlElement* root = doc.RootElement();
	if(root == nullptr)
	{
		return false;
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
	//m_pScene->Save(
	TiXmlDocument doc;

	USES_CONVERSION;
	TiXmlNode* pRoot = doc.InsertEndChild(TiXmlElement("project"));

	TiXmlElement scene("scene");

	scene.InsertEndChild(TiXmlText(m_pScene->GetFileName().string().c_str()));
	pRoot->InsertEndChild(scene);
	
	TiXmlElement clearClr("clear_color");

	char szBuffer[1024];

	sprintf_s(szBuffer,1024, "%.3f,%.3f,%.3f,%.3f", m_clearClr.r, m_clearClr.g, m_clearClr.b, m_clearClr.a);

	clearClr.InsertEndChild(TiXmlText(szBuffer));

	pRoot->InsertEndChild(clearClr);

	if(false == doc.SaveFile(W2A(filename)))
	{
		return false;
	}

	m_filePath = filename;
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

	//s_Allocator.Release();
}

void Project::CreateObject_Empty()
{
	m_pScene->CreateObject_Empty();
}
engine::GameObjectPtr Project::CreateObject(const std::wstring& name)
{
	return m_pScene->CreateObject(name);
}
engine::GameObjectPtr Project::CreateObjectFromTpl(const std::wstring& name, const std::wstring& tpl)
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
	Close();

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
	return m_pScene->CreateGameObjectComponent(name);
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
	if(m_pScene == nullptr)
	{
		return engine::GameObjectPtr();
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

	if(false == CopyDirectory(init / path(L"assets"), tar / path(L"assets")))
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
	return true;
}
bool Project::CopyDirectory(boost::filesystem::path src, boost::filesystem::path dst)
{
	namespace fs = boost::filesystem;
	try
	{
		// Check whether the function call is valid
		if( !fs::exists(src) || !fs::is_directory(src))
		{
			return false;
		}
		if(fs::exists(dst))
		{
			return false;
		}
		// Create the destination directory
		if(!fs::create_directory(dst))
		{
			return false;
		}
	}
	catch(fs::filesystem_error const & e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}
	// Iterate through the source directory
	for(fs::directory_iterator file(src); file != fs::directory_iterator(); ++file)
	{
		try
		{
			fs::path current(file->path());
			if(fs::is_directory(current))
			{
				// Found directory: Recursion
				if(!CopyDirectory(current, dst / current.filename()))
				{
					return false;
				}
			}
			else
			{
				// Found file: Copy
				fs::copy_file(current, dst / current.filename());
			}
		}
		catch(fs::filesystem_error const & e)
		{
			std:: cerr << e.what() << std::endl;
		}
	}
	return true;
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
	return m_pScene->Save(filename);
}
bool Project::LoadScene(const _TCHAR* filename)
{
	return m_pScene->Load(filename);
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