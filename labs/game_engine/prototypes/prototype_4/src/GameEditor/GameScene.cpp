#include "stdafx.h"
#include "GameScene.h"


GameScene::GameScene(void)
{
	m_strFile = L"";
}


GameScene::~GameScene(void)
{
}
bool GameScene::New()
{
	m_strFile = L"";
	return true;
}

bool GameScene::Load(const wchar_t* szFile)
{
	m_strFile = szFile;
	return true;
}
bool GameScene::Save(const wchar_t* szFile)
{
	m_strFile = szFile;
	return true;
}
const std::wstring& GameScene::GetFileName()
{
	return m_strFile;
}
void GameScene::Close()
{
	m_strFile = L"";
}
