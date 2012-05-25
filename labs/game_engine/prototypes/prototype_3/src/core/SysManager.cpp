#include "core_pch.h"
#include "SysManager.h"

namespace engine
{
	SysManager::SysManager(void)
	{
	}


	SysManager::~SysManager(void)
	{
	}

	SysGraphicsPtr	SysManager::LoadSysGraphics(const wchar_t* szFile)
	{
		m_graphicsMod.hLib = ::LoadLibrary(szFile);
		if(m_graphicsMod.hLib == NULL)
		{
			return SysGraphicsPtr();
		}


		Sys_GraphicsMod::Fn_CreateSys CreateSys = (Sys_GraphicsMod::Fn_CreateSys)GetProcAddress(m_graphicsMod.hLib, "CreateSys");
		if(CreateSys == NULL)
		{
			return SysGraphicsPtr();
		}

		m_graphicsMod.filename = szFile;
		m_graphicsMod.pSys = SysGraphicsPtr(CreateSys(), boost::bind(&Sys_GraphicsMod::delete_sys, m_graphicsMod, _1));



		return m_graphicsMod.pSys;
	}
	SysInputPtr SysManager::LoadSysInput(const wchar_t* szFile)
	{

		m_inputMod.hLib = ::LoadLibrary(szFile);
		if(m_inputMod.hLib == NULL)
		{
			return SysInputPtr();
		}


		Sys_InputMod::Fn_CreateSys CreateSys = (Sys_InputMod::Fn_CreateSys)GetProcAddress(m_inputMod.hLib, "CreateSys");
		if(CreateSys == NULL)
		{
			return SysInputPtr();
		}

		m_inputMod.filename = szFile;
		m_inputMod.pSys = SysInputPtr(CreateSys(), boost::bind(&Sys_InputMod::delete_sys, m_inputMod, _1));



		return m_inputMod.pSys;

	}
	

}
