#include "StdAfx.h"
#include "Project.h"

ProjectPtr				Project::m_pProject;

Project::Project(void)
{
}


Project::~Project(void)
{
}
bool Project::New(const _TCHAR* name)
{
	Release();
	
	m_name = name;


	return true;
}
void Project::Load()
{
}
bool Project::Save()
{
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