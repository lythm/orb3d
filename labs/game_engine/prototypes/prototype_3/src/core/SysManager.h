#pragma once


namespace engine
{
	class SysManager
	{

		template<typename Sys>
		struct Sys_Mod_T
		{
			typedef Sys*					(*Fn_CreateSys)();
			typedef void					(*Fn_DestroySys)(Sys*);
			
			boost::shared_ptr<Sys>			pSys;

			HMODULE							hLib;
			std::wstring					filename;

			void							delete_sys(Sys* pSys)
			{

				if(hLib == NULL)
				{
					return;
				}
				Fn_DestroySys DestroySys = (Fn_DestroySys)GetProcAddress(hLib, "DestroySys");

				if(DestroySys == NULL)
				{
					return;

				}

				DestroySys(pSys);

				FreeLibrary(hLib);
				hLib = NULL;
			}
		};

		typedef Sys_Mod_T<SysInput>			Sys_InputMod;

		typedef Sys_Mod_T<SysGraphics>		Sys_GraphicsMod;
				
	public:
		SysManager(void);
		virtual ~SysManager(void);


		SysGraphicsPtr						LoadSysGraphics(const wchar_t* szFile);
	
		SysInputPtr							LoadSysInput(const wchar_t* szFile);

	private:


	private:

		Sys_GraphicsMod						m_graphicsMod;
		Sys_InputMod						m_inputMod;
		
	};

}