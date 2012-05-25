#pragma once

namespace orb
{
	class SMManager
	{
	public:
		struct ServiceModDesc
		{
			std::wstring						modFile;
			ServiceMod*							pModObj;
			ServiceModClass*					pClass;
			kernel_object						lib;
		};

		SMManager();
		virtual ~SMManager();


		bool								Initialize();
		void								Release();

		void								ListSM();
	private:
		bool								LoadMod(const std::wstring& name);
		
	private:
		std::vector<ServiceModDesc>			m_mods;
	};
};
