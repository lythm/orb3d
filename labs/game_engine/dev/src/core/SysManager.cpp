#include "core_pch.h"
#include "core\SysManager.h"

namespace ld3d
{
	SysManager::SysManager(void)
	{
	}


	SysManager::~SysManager(void)
	{
	}

	Sys_GraphicsPtr	SysManager::LoadSysGraphics(const wchar_t* szFile)
	{
		if(m_graphicsMod.load_sys(szFile) == false)
		{
			return Sys_GraphicsPtr();
		}
	
		return m_graphicsMod.pSys;
	}
	Sys_InputPtr SysManager::LoadSysInput(const wchar_t* szFile)
	{
		if(m_inputMod.load_sys(szFile) == false)
		{
			return Sys_InputPtr();
		}
		
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

	Sys_SoundPtr SysManager::LoadSysSound(const wchar_t * szFile)
	{
		if(m_soundMod.load_sys(szFile) == false)
		{
			return Sys_SoundPtr();
		}
		return m_soundMod.pSys;
	}
	Sys_SoundPtr SysManager::GetSys_Sound()
	{
		return m_soundMod.pSys;
	}
}
