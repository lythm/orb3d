#pragma once
#include <string>
#include <vector>
#include <map>
#include <boost\shared_ptr.hpp>
#include <boost\function.hpp>


namespace ld3d
{
	enum PropType
	{
		property_type_unknown,
		property_type_bool,
		property_type_int,
		property_type_string,
		property_type_float,
		property_type_pointer,

		property_type_custum,
	};

	template <typename T>
	struct PropTypeId
	{
		static PropType				m_type;
	};

	template <typename T>
	PropType PropTypeId<T>::m_type					= property_type_unknown;
	template <>
	PropType PropTypeId<bool>::m_type				= property_type_bool;
	template <>
	PropType PropTypeId<int>::m_type				= property_type_int;
	template <>
	PropType PropTypeId<float>::m_type				= property_type_float;
	template <>
	PropType PropTypeId<std::wstring>::m_type		= property_type_string;
	template <>
	PropType PropTypeId<void*>::m_type				= property_type_pointer;

	class Property
	{
	public:


	public:
		Property(const std::wstring& szName, PropType type = property_type_unknown, void* data = nullptr)
		{
			m_type						= type;
			m_name						= szName;
			m_data						= nullptr;
		}
		virtual ~Property(void)
		{
		}

		PropType					getType() const{return m_type;}
		void						setType(PropType t){m_type = t;}
		const std::wstring&			getName() const{return m_name;}
		void						setName(const std::wstring& name){m_name = name;}
		void						setData(void* pData){m_data = pData;}
		void*						getData(){return m_data;}

	private:

		PropType					m_type;
		std::wstring				m_name;
		void*						m_data;
	};

	template <typename T>
	class Property_T : public Property
	{
	public:
		typedef boost::function<void (const T&)>				Setter_T;
		typedef boost::function<const T& ()>					Getter_T;

		Property_T(const std::wstring& szName, PropType type = property_type_unknown, void* data = nullptr, Setter_T setter = Setter_T(), Getter_T getter = Getter_T()) : Property(szName, type, data)
		{
			m_setter = setter;
			m_getter = getter;
		}

		bool						IsReadOnly()
		{
			return m_setter.empty();
		}

		void						Set(const T& val)
		{
			m_setter(val);
		}
		const T&					Get()
		{
			return m_getter();
		}

		Setter_T					m_setter;
		Getter_T					m_getter;

	};

	class PropertySet
	{

	public:
		PropertySet(const std::wstring& name);
		virtual ~PropertySet(void);

		bool								addProperty(boost::shared_ptr<Property> p);
		unsigned long						getPropertyCount();
		Property*							getProperty(int iProp);

		Property*							getProperty(const wchar_t* szName);
		void								clearProperties();

		bool								hasProperty(const wchar_t* szName);

		const std::wstring&					getName(){return m_name;}
	private:
		std::vector<boost::shared_ptr<Property> >
			m_props;

		std::map<const wchar_t*, size_t>	m_nameTable;

		std::wstring						m_name;
	};
}
