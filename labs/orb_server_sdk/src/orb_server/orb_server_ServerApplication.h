#pragma once


namespace orb
{
	class Application
	{
	public:
		

		static Application*				Instance();

		bool							Initialize();
		void							Release();
		void							Run();

		Core*							GetCore();

		void							PrintSysMessage(const std::wstring& msg);
	private:
		Application(void);
		virtual ~Application(void);
	private:
		
		static Application				s_inst;

		Core*							m_pCore;
		
	};
}
