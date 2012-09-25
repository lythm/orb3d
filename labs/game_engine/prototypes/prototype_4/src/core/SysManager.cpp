#include "core_pch.h"
#include "core\SysManager.h"

namespace engine
{
	SysManager::SysManager(void)
	{
	}


	SysManager::~SysManager(void)
	{
	}

	Sys_GraphicsPtr	SysManager::LoadSysGraphics(const wchar_t* szFile)
	{
		m_graphicsMod.hLib = ::LoadLibrary(szFile);
		if(m_graphicsMod.hLib == NULL)
		{
			return Sys_GraphicsPtr();
		}


		Sys_GraphicsMod::Fn_CreateSys CreateSys = (Sys_GraphicsMod::Fn_CreateSys)GetProcAddress(m_graphicsMod.hLib, "CreateSys");
		if(CreateSys == NULL)
		{
			return Sys_GraphicsPtr();
		}

		m_graphicsMod.filename = szFile;
		m_graphicsMod.pSys = Sys_GraphicsPtr(CreateSys(), boost::bind(&Sys_GraphicsMod::delete_sys, m_graphicsMod, _1));



		return m_graphicsMod.pSys;
	}
	Sys_InputPtr SysManager::LoadSysInput(const wchar_t* szFile)
	{

		m_inputMod.hLib = ::LoadLibrary(szFile);
		if(m_inputMod.hLib == NULL)
		{
			return Sys_InputPtr();
		}


		Sys_InputMod::Fn_CreateSys CreateSys = (Sys_InputMod::Fn_CreateSys)GetProcAddress(m_inputMod.hLib, "CreateSys");
		if(CreateSys == NULL)
		{
			return Sys_InputPtr();
		}

		m_inputMod.filename = szFile;
		m_inputMod.pSys = Sys_InputPtr(CreateSys(), boost::bind(&Sys_InputMod::delete_sys, m_inputMod, _1));



		return m_inputMod.pSys;

	}

	Sys_InputPtr SysManager::GetSysInput()
	{
		return m_inputMod.pSys;
	}

	Sys_GraphicsPtr	SysManager::GetSysGraphics()
	{
		return m_graphicsMod.pSys;
	}

}
