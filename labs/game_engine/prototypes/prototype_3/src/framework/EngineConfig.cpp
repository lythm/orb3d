#include "framework_pch.h"
#include "EngineConfig.h"


namespace engine
{
	EngineConfig::EngineConfig(void)
	{
	}


	EngineConfig::~EngineConfig(void)
	{
	}
	const std::vector<std::wstring>& EngineConfig::Settings(const std::wstring& key)
	{
		return m_settings[key];
	}

	std::wstring EngineConfig::Settings(const std::wstring& key, uint8 index)
	{
		const std::vector<std::wstring>& s = Settings(key);

		if(s.size() <= index)
		{
			return L"_null_";
		}

		return s[index]; 
	}

	bool EngineConfig::Load(const char* cfg)
	{
		FILE* file = fopen(cfg, "r");

		if(file == NULL)
			return false;

		wchar_t szLine[1024];
		
		while(NULL != fgetws(szLine, 1023, file))
		{
			ParseLine(szLine);
		}

		fclose(file);
		
	
		return true;
	}

	bool EngineConfig::Save(const char* cfg)
	{
		FILE* file = fopen(cfg, "w+");

		if(file == NULL)
			return false;

		
		std::map<std::wstring, std::vector<std::wstring> >::iterator it = m_settings.begin();

		for(;it != m_settings.end(); ++it)
		{
			const std::vector<std::wstring>& v = it->second;

			for(size_t i = 0; i < v.size(); ++i)
			{

				fwprintf(file, L"%s\t%s\n", it->first.c_str(), v[i].c_str());
			}

		}


		fclose(file);

		return true;
	}
	void EngineConfig::ReplaceWhiteRight(wchar_t* line, wchar_t c)
	{
		wchar_t* ptr = line + wcslen(line) - 1;

		while(ptr != line && (*ptr == L' ' || *ptr == L'\t' || *ptr == L'\n'))
		{
			*ptr = c;
			--ptr;
		}

	}
	wchar_t* EngineConfig::ReplaceWhiteLeft(wchar_t* line, wchar_t c)
	{
		while(*line != 0 && (*line == L' ' || *line == L'\t' || *line == L'\n'))
		{
			*line = c;
			line++;
		}

		return line;
	}
	wchar_t* EngineConfig::FindWhite(wchar_t* line)
	{
		while(*line != 0 && (*line != L' ' && *line != L'\t' && *line != L'\n') )
		{
			line++;
		}
		return line;
	}
	void EngineConfig::ParseLine(wchar_t* line)
	{
		if(line[0] == 0 || line[0] == L'#')
			return;

		wchar_t* key = ReplaceWhiteLeft(line, 0);

		wchar_t* value = FindWhite(key);

		value = ReplaceWhiteLeft(value, 0);

		if(*key == 0)
			return;

		if(*value == 0)
			return;

		ReplaceWhiteRight(value, 0);

		if(*value == 0)
			return;

		m_settings[key].push_back(value);
	}
}