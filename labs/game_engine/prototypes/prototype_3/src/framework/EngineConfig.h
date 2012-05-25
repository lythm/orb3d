#pragma once


namespace engine
{
	class EngineConfig
	{
	public:
		EngineConfig(void);
		virtual ~EngineConfig(void);

		bool										Load(const char* cfg);
		bool										Save(const char* cfg);

		const std::vector<std::wstring>&			Settings(const std::wstring& key);

		std::wstring								Settings(const std::wstring& key, uint8 index);
	private:
		void										ParseLine(wchar_t* line);
		wchar_t*										ReplaceWhiteLeft(wchar_t* line, wchar_t c);
		wchar_t*										FindWhite(wchar_t* line);
		void										ReplaceWhiteRight(wchar_t* line, wchar_t c);
	private:
		std::map<std::wstring, 
					std::vector<std::wstring> >		m_settings;
	};


}