#pragma once


namespace orb
{
	class SysConfig
	{
	public:
		SysConfig(void);
		virtual ~SysConfig(void);

		bool										Load(const char* cfg);

		const std::vector<std::wstring>&			Settings(const std::wstring& key);
	private:
		void										ParseLine(w_char* line);
		w_char*										ReplaceWhiteLeft(w_char* line, w_char c);
		w_char*										FindWhite(w_char* line);
		void										ReplaceWhiteRight(w_char* line, w_char c);
	private:
		std::map<std::wstring, 
					std::vector<std::wstring> >		m_settings;
	};
}
