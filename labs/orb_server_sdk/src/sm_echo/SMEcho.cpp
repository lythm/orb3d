#include "SMEcho.h"


#include <boost/uuid/string_generator.hpp>

static SMEchoClass g_echoClass;

orb::ServiceModClass* GetServiceModClass()
{
	return &g_echoClass;
}


SMEcho::SMEcho(void) : ServiceMod(boost::uuids::uuid(boost::uuids::string_generator()("A387079B-6F04-45AD-9BC5-221C762F96D4")))
{
}


SMEcho::~SMEcho(void)
{
}
bool SMEcho::Install(orb::Core* pCore)
{
	return true;
}
void SMEcho::Uninstall()
{
}

orb::ServiceMod* SMEchoClass::CreateObject()
{
	return new SMEcho;
}
void SMEchoClass::DeleteObject(orb::ServiceMod* pMod)
{
	delete (SMEcho*)pMod;
}
