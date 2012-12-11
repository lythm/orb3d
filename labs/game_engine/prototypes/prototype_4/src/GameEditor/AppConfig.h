#pragma once
class AppConfig
{
public:
	AppConfig(void);
	virtual ~AppConfig(void);

	std::wstring												Value(const std::wstring& key);
	void														Set(const std::wstring& key, const std::wstring& val);

	bool														Load(const std::wstring& file);
	bool														Save(const std::wstring& file);
private:
	boost::unordered_map<std::wstring, std::wstring>			m_configs;
};

