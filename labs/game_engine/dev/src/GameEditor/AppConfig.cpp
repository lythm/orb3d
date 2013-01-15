#include "StdAfx.h"
#include "AppConfig.h"


AppConfig::AppConfig(void)
{
}


AppConfig::~AppConfig(void)
{
}
std::wstring AppConfig::Value(const std::wstring& key)
{
	if(m_configs.find(key) == m_configs.end())
	{
		return std::wstring();
	}
	return m_configs[key];
}
void AppConfig::Set(const std::wstring& key, const std::wstring& val)
{
	m_configs[key] = val;
}
bool AppConfig::Load(const std::wstring& key)
{
	return true;
}
bool AppConfig::Save(const std::wstring& file)
{
	return true;
}