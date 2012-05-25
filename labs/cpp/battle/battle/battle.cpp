// battle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Battle.h"

#include "Entity.h"
#include "UnitAttributes.h"

#include "EventDispatcher.h"



void Loop();

void OnUnknownEvent(int id, const int&e)
{
	printf("unknown event:%d-%d\n", id, e);
}
void OnEvent(int id, const int& e)
{
	//printf("%d-%d\n", id, e);

}
int _tmain(int argc, _TCHAR* argv[])
{

	/*EventDispatcher<int> disp; 

	int a = 100;

	disp.AddUnhandledEventHandler(OnUnknownEvent);

	disp.AddEventHandler(0, OnEvent);
	disp.AddEventHandler(1, OnEvent);


	int tick = GetTickCount();
	int count = 100000000;
	for(int i = 0; i < count; ++i)
	{
		disp.DispatchEvent(0, 100); 
	}

	float sec = (GetTickCount() - tick) / 1000.0f;

	printf("sec: %.4f call/sec: %.4f\n", sec, count / sec);*/

	Entity* pEntity = new Entity;


	pEntity->RegisterComponent(new UnitAttributes);


	UnitAttributes* pAttr = (UnitAttributes*)pEntity->GetComponent(0);


	pAttr->Set(UnitAttributes::FIELD_STR, 100);

	float v = pAttr->Get<float>(UnitAttributes::FIELD_STR);

	while(true)
	{
		pEntity->Update(0);
		Loop();


		Sleep(1);
	}



	return 0;
}

void Loop()
{
}
