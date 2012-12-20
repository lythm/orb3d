#include "StdAfx.h"
#include "Project.h"
#include <afxconv.h>
#include "AppContext.h"


ProjectPtr				Project::m_pProject;

Project::Project(void)
{
	m_bEmpty = true;
}


Project::~Project(void)
{
}
bool Project::IsEmpty()
{
	return m_bEmpty;
}
bool Project::New()
{

	if(AppContext::GetRenderSystem()->GetLightCount() == 0)
	{
		AddDefaultLight();
	}

	AppContext::UpdateObjectView();
	m_bEmpty = false;
	return true;
}
bool Project::Load(const _TCHAR* filename)
{
	m_filePath = filename;

	USES_CONVERSION;

	TiXmlDocument doc;

	doc.LoadFile(W2A(filename));


	if(AppContext::GetRenderSystem()->GetLightCount() == 0)
	{
		AddDefaultLight();
	}

	m_bEmpty = false;

	AppContext::UpdateObjectView();
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
	AppContext::GetCoreApi()->GetRoot()->Clear();
	m_bEmpty = true;
}
ProjectPtr Project::Instance()
{
	if(m_pProject == NULL)
	{
		m_pProject = ProjectPtr(new Project);
	}

	return m_pProject;
}
void Project::AddDefaultLight()
{
	using namespace engine;
	using namespace engine;

	GameObjectPtr pObj = AppContext::CreateGameObject(L"Default Light");
		
	Light_DirPtr pLight = boost::shared_dynamic_cast<Light_Dir>(AppContext::GetCoreApi()->CreateGameObjectComponent(L"DirectionalLight"));
	pLight->SetRenderSystem(AppContext::GetCoreApi()->GetRenderSystem());

	pObj->AddComponent(pLight);

	pObj->SetTranslation(1, 1, 1);
	pObj->LookAt(math::Vector3(0, 0, 0));

}
