#pragma once


class GameScene
{
public:
	GameScene(void);
	virtual ~GameScene(void);

	bool										Load(const wchar_t* szFile);
	void										Save(const wchar_t* szFile);


private:

};

