#include "StdAfx.h"
#include "Project.h"
#include <afxconv.h>
#include "AppContext.h"


ProjectPtr				Project::m_pProject;

Project::Project(void)
{
}


Project::~Project(void)
{
}
bool Project::New()
{
	if(AppContext::GetRenderSystem()->GetLightCount() == 0)
	{
		AddDefaultLight();
	}

	AppContext::UpdateObjectView();

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

	GameObjectPtr pObj = AppContext::CreateGameObject(L"DefaultLight");
		
	LightDataPtr pLight = boost::shared_dynamic_cast<object_component::LightData>(AppContext::GetCoreApi()->CreateGameObjectComponent(L"Light"));
	pLight->SetRenderSystem(AppContext::GetCoreApi()->GetRenderSystem());
	pLight->CreateLight(LT_DIRLIGHT);

	pObj->AddComponent(pLight);
}
