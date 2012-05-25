#include "core_pch.h"
#include "..\..\include\core\SceneManager.h"
#include "graphics\Sys_Graphics.h"

namespace engine
{
	SceneManager::SceneManager(void)
	{
	}


	SceneManager::~SceneManager(void)
	{
	}
	bool SceneManager::Initialize(Sys_GraphicsPtr pGraphics)
	{
		m_pGraphics = pGraphics;
		return true;
	}
	void SceneManager::Release()
	{
	}
	void SceneManager::Update()
	{
	}
	void SceneManager::Render()
	{
		m_pGraphics->Render();
	}
}
