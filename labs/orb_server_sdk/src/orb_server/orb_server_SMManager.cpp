#include "orb_server_pch.h"
#include "orb_server_SMManager.h"

namespace orb
{
	SMManager::SMManager()
	{
	}
	SMManager::~SMManager()
	{
	}
	bool SMManager::Initialize()
	{
		using namespace boost::filesystem;

		const std::vector<std::wstring>& mod_dirs = GetCore()->AppSettings(L"mod_dir");

		for(size_t i = 0; i < mod_dirs.size(); ++i)
		{
			std::wstring dir = mod_dirs[i];

			wpath search_path(dir);
			wdirectory_iterator dir_it(search_path);
			wdirectory_iterator end_it;
			for(; dir_it != end_it; ++dir_it)
			{
				if ( is_directory(dir_it->status()) )
				{
					continue;
				}

				if(true == LoadMod(dir_it->path().string()))
				{
					PrintSysMessage(std::wstring(L"sm ") + dir_it->path().string() + std::wstring(L" installed."));

				}
			}
		}

	

	return true;
}
void SMManager::Release()
{
	for(size_t i = 0; i < m_mods.size(); ++i)
	{
		m_mods[i].pModObj->Uninstall();
		m_mods[i].pClass->DeleteObject(m_mods[i].pModObj);
		os::close_library(m_mods[i].lib);

		PrintSysMessage(L"sm " + m_mods[i].modFile + L" uninstalled.");
	}

	m_mods.clear();
	return;
}
bool SMManager::LoadMod(const std::wstring& name)
{
	ServiceModDesc m;
	m.lib = os::open_library(name.c_str());
	if(m.lib == NULL)
		return false;

	PTR_GET_MODCLASS ptr_get_class = (PTR_GET_MODCLASS)os::load_func(m.lib, FUNC_GET_MODCLASS_NAME);
	if(ptr_get_class == NULL)
	{
		os::close_library(m.lib);
		return false;
	}

	m.pClass = ptr_get_class();
	if(m.pClass == NULL)
	{
		os::close_library(m.lib);
		return false;
	}

	m.pModObj = m.pClass->CreateObject();

	m.pModObj->Install(GetCore());
	m.modFile = name;

	m_mods.push_back(m);

	return true;
}
void SMManager::ListSM()
{

	for(size_t i = 0; i < m_mods.size(); ++i)
	{
		PrintSysMessage(L"sm: " + m_mods[i].modFile);
	}

	w_char buffer[100];

	swprintf(buffer, 100, L"%d service modules installed.", m_mods.size());

	PrintSysMessage(buffer);
}
}
