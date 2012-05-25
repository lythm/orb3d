#include "orb_server_pch.h"
#include "orb_server_SysConfig.h"


namespace orb
{

	SysConfig::SysConfig(void)
	{
	}


	SysConfig::~SysConfig(void)
	{
	}
	const std::vector<std::wstring>& SysConfig::Settings(const std::wstring& key)
	{
		return m_settings[key];
	}
	bool SysConfig::Load(const char* cfg)
	{
		FILE* file = fopen(cfg, "r");

		if(file == NULL)
			return false;

		w_char szLine[1024];
		
		while(NULL != fgetws(szLine, 1023, file))
		{
			ParseLine(szLine);
		}

		fclose(file);
		
		PrintSysMessage(L"config loaded.");

		return true;
	}
	void SysConfig::ReplaceWhiteRight(w_char* line, w_char c)
	{
		w_char* ptr = line + wcslen(line) - 1;

		while(ptr != line && (*ptr == L' ' || *ptr == L'\t' || *ptr == L'\n'))
		{
			*ptr = c;
			--ptr;
		}

	}
	w_char* SysConfig::ReplaceWhiteLeft(w_char* line, w_char c)
	{
		while(*line != 0 && (*line == L' ' || *line == L'\t' || *line == L'\n'))
		{
			*line = c;
			line++;
		}

		return line;
	}
	w_char* SysConfig::FindWhite(w_char* line)
	{
		while(*line != 0 && (*line != L' ' && *line != L'\t' && *line != L'\n') )
		{
			line++;
		}
		return line;
	}
	void SysConfig::ParseLine(w_char* line)
	{
		if(line[0] == 0 || line[0] == L'#')
			return;

		w_char* key = ReplaceWhiteLeft(line, 0);

		w_char* value = FindWhite(key);

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
