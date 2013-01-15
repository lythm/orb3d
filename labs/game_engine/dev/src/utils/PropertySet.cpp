#include "utils_pch.h"
#include "..\..\include\utils\PropertySet.h"

namespace ld3d
{
	PropertySet::PropertySet(const std::wstring& name)
	{
		m_name = name;
	}

	PropertySet::~PropertySet(void)
	{
		clearProperties();
	}
	unsigned long PropertySet::getPropertyCount()
	{
		return (unsigned long)m_props.size();
	}
	Property* PropertySet::getProperty(int iProp)
	{
		return m_props[iProp].get();
	}
	void PropertySet::clearProperties()
	{
		m_props.clear();
		m_nameTable.clear();
	}
	Property* PropertySet::getProperty(const wchar_t* szName)
	{
		size_t i = m_nameTable[szName];
		return m_props[i].get();
	}
	bool PropertySet::hasProperty(const wchar_t* szName)
	{
		return m_nameTable.find(szName) != m_nameTable.end();
	}
	bool PropertySet::addProperty(boost::shared_ptr<Property> p)
	{
		if(p->getType() == property_type_unknown)
		{
			return false;
		}

		m_props.push_back(p);
		m_nameTable[p->getName().c_str()] = m_props.size() - 1;

		return true;
	}
}