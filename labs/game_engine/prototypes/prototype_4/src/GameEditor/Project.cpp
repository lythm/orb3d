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
	Release();
	


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
		AppContext::AddDefaultLight();
	}
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
void Project::Release()
{

}
ProjectPtr Project::Instance()
{
	if(m_pProject == NULL)
	{
		m_pProject = ProjectPtr(new Project);
	}

	return m_pProject;
}
