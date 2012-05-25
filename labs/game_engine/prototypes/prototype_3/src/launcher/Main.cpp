#include <tchar.h>
#include "LauncherApp.h"



int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LauncherApp app;

	if(false == app.Initialize(hInstance, L"WinApp", 800, 600))
	{
		return -1;
	}
	app.Run();

	app.Release();

	return 0;
}
