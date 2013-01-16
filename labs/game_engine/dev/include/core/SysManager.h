#pragma once


namespace ld3d
{
	class EXPORT_CLASS SysManager
	{

		template<typename Sys>
		struct Sys_Mod_T
		{
			typedef Sys*					(*Fn_CreateSys)();
			typedef void					(*Fn_DestroySys)(Sys*);

			boost::shared_ptr<Sys>			pSys;

			HMODULE							hLib;
			std::wstring					filename;


			bool							load_sys(const wchar_t* file)
			{
				hLib = ::LoadLibrary(file);
				if(hLib == NULL)
				{
					return false;
				}


				Fn_CreateSys CreateSys = (Fn_CreateSys)GetProcAddress(hLib, "CreateSys");
				if(CreateSys == NULL)
				{
					FreeLibrary(hLib);
					return false;
				}

				filename = file;
				pSys = boost::shared_ptr<Sys>(CreateSys(), boost::bind(&Sys_Mod_T<Sys>::delete_sys, this, _1));



				return pSys;
			}

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

		typedef Sys_Mod_T<Sys_Input>			Sys_InputMod;

		typedef Sys_Mod_T<Sys_Graphics>			Sys_GraphicsMod;

		typedef Sys_Mod_T<Sys_Sound>			Sys_SoundMod;
	public:
		SysManager(void);
		virtual ~SysManager(void);


		Sys_GraphicsPtr							LoadSysGraphics(const wchar_t* szFile);
		Sys_InputPtr							LoadSysInput(const wchar_t* szFile);
		Sys_SoundPtr							LoadSysSound(const wchar_t * szFile);
		
		Sys_SoundPtr							GetSys_Sound();
		Sys_InputPtr							GetSysInput();
		Sys_GraphicsPtr							GetSysGraphics();
	private:


	private:

		Sys_GraphicsMod							m_graphicsMod;
		Sys_InputMod							m_inputMod;
		Sys_SoundMod							m_soundMod;

	};

}