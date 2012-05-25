#pragma once

#include "orb_server_sdk.h"

class SMEcho : public orb::ServiceMod
{
public:
	SMEcho(void);
	virtual ~SMEcho(void);

	bool						Install(orb::Core* pCore);
	void						Uninstall();
};

class SMEchoClass : public orb::ServiceModClass
{
public:
	orb::ServiceMod*			CreateObject();
	void						DeleteObject(orb::ServiceMod* pMod);

};


_DLL_API orb::ServiceModClass* GetServiceModClass();
