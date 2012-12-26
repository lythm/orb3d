#include "StdAfx.h"
#include "Project.h"
#include <afxconv.h>
#include "AppContext.h"


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

void Project::AddDefaultLight()
{
	using namespace engine;
	using namespace engine;

	GameObjectPtr pObj = AppContext::CreateGameObject(L"Default Light");
		
	Light_SkyPtr pLight = boost::shared_dynamic_cast<Light_Sky>(AppContext::CreateGameObjectComponent(L"SkyLight"));
	pLight->SetRenderSystem(AppContext::GetCoreApi()->GetRenderSystem());

	pObj->AddComponent(pLight);

	pObj->SetTranslation(1, 1, 1);
	pObj->LookAt(math::Vector3(0, 0, 0));

}
