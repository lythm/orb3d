#include "StdAfx.h"
#include "UnitAttributes.h"


UnitAttributes::UnitAttributes(void)
{
	memset(&m_attrs, 0, sizeof(Attr) * FIELD_COUNT);
}


UnitAttributes::~UnitAttributes(void)
{
}
int UnitAttributes::GetId()
{
	return 0;
}
