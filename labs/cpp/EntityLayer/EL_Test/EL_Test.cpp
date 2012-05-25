// EL_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\entitylayer\entity.h"
#include "..\entitylayer\entitymanager.h"


int _tmain(int argc, _TCHAR* argv[])
{
	EntityManager* pManager = new EntityManager;

	Entity* pCharacter = pManager->CreateEntity(0);


	return 0;
}

