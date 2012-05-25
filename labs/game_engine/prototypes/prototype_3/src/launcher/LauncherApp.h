#pragma once

#include "WinApp.h"

#include "engine_all.h"


class LauncherApp : public WinApp
{
public:
	LauncherApp(void);
	virtual ~LauncherApp(void);


	void											OnUpdate();
	bool											OnInit();
	void											OnRelease();


private:
	engine::EngineMainPtr							m_pEngine;
};

