#pragma once


class GameScene
{
public:
	GameScene(void);
	virtual ~GameScene(void);

	bool										Load(const wchar_t* szFile);
	bool										Save(const wchar_t* szFile);
	void										Close();
	bool										New();

	const std::wstring&							GetFileName();

private:
	std::wstring								m_strFile;
};

