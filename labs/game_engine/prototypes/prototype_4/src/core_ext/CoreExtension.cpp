#include "core_ext_pch.h"
#include "CoreExtension.h"



//EXPORT_C_API Game* CreateGame()
//{
//	return new Game;
//}
//
//EXPORT_C_API void DestroyGame(engine::GameInterface* pGame)
//{
//	delete (Game*)pGame;
//}
//


EXPORT_C_API engine::Extension* CreateExtension(engine::CoreApi pCore)
{

	return nullptr;
	
}


EXPORT_C_API void DestroyExtension(engine::Extension* pExt)
{

}



namespace engine
{
	CoreExtension::CoreExtension(void)
	{
	}


	CoreExtension::~CoreExtension(void)
	{
	}

}
