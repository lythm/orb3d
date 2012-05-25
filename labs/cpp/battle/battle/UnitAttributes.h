#pragma once

#include "EntityComponent.h"

class UnitAttributes : public EntityComponent
{
public:
	struct Attr
	{
		union
		{
			float								fVal;
			__int64								iVal;
			bool								bVal;

			__int64								copy;
		};
	};

	enum ATTR_FIELD
	{
		FIELD_STR,
		FIELD_TYPE,

		FIELD_COUNT,
	};
public:
	UnitAttributes(void);
	virtual ~UnitAttributes(void);


	int											GetId();

	template<typename T>
	T											Get(ATTR_FIELD field)
	{
		return *((T*)(&m_attrs[field].copy));
	}


	template<typename T>
	void										Set(ATTR_FIELD field, const T& val)
	{
		*((T*)(&m_attrs[field].copy)) = val;
	}

private:

	Attr										m_attrs[FIELD_COUNT];
};

