#include "StdAfx.h"
#include "Project.h"


Project::Project(void)
{
}


Project::~Project(void)
{
}
bool Project::New(const _TCHAR* name)
{
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
