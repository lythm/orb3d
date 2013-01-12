#include "StdAfx.h"
#include "Project.h"
#include <afxconv.h>
#include "AppContext.h"


Project::Project(void)
{
	m_objNo	= 0;
}


Project::~Project(void)
{
}

bool Project::New(const _TCHAR* filename)
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
	AppContext::GetCoreApi()->ResetScene();
}

void Project::AddDefaultLight()
{
	using namespace engine;
	using namespace engine;

	GameObjectPtr pObj = AppContext::CreateGameObjectFromTemplate(L"Default Light", L"SkyLight");
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
	
	GameObjectPtr pObj = AppContext::CreateGameObject(full_name.GetString());

	m_objNo++;
	return pObj;
}
engine::GameObjectPtr Project::CreateObjectFromTpl(const std::wstring& name, const std::wstring& tpl)
{
	using namespace engine;

	CString full_name;

	full_name.Format(L"%s-%d", name.c_str(), m_objNo);
	
	GameObjectPtr pObj = AppContext::CreateGameObjectFromTemplate(full_name.GetString(), tpl);

	m_objNo++;
	return pObj;
}
