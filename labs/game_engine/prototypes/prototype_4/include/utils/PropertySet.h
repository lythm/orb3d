#pragma once
#include <string>
#include <vector>
#include <map>
#include <boost\shared_ptr.hpp>
#include <boost\function.hpp>


namespace engine
{
	class Property
	{
	public:

		enum PropType
		{
			type_unknown,
			type_bool,
			type_int,
			type_string,
			type_float,
			type_pointer,

			type_custum,
		};
	public:
		Property(const std::wstring& szName, PropType type = type_unknown, void* data = nullptr)
		{
			m_type						= type;
			m_name						= szName;
			m_data						= nullptr;
		}
		~Property(void)
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
	struct PropTypeId
	{
		static Property::PropType			m_type;
	};
	template <typename T>
	class Property_T : public Property
	{
	public:
		typedef boost::function<void (const T&)>				Setter_T;
		typedef boost::function<const T& ()>					Getter_T;

		Property_T(const std::wstring& szName, PropType type = type_unknown, void* data = nullptr, Setter_T setter = Setter_T(), Getter_T getter = Getter_T()) : Property(szName, type, data)
		{
			m_setter = setter;
			m_getter = getter;
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
#if 0
	class Property
	{
	public:

		enum PropType
		{
			type_unknown,
			type_bool,
			type_int,
			type_string,
			type_float,
			type_pointer,

			type_custum,
		};
	public:
		Property(const wchar_t* szName, PropType type, void* val)
		{
			m_type						= type;
			m_name						= szName;
			m_val						= val;
			m_data						= nullptr;
		}
		~Property(void)
		{
		}


		PropType					getType() const{return m_type;}
		const std::wstring&			getName() const{return m_name;}

		template<typename T>
		T*							getValPtr()
		{
			return (T*)m_val;
		}
		template<typename T>
		T							getVal()
		{
			return *getValPtr<T>();
		}

		template<typename T>
		void						setVal(const T& val)
		{
			*((T*)m_val)	= val;
		}

		void*						getPointerVal()
		{
			return *(void**)m_val;
		}
		void						setPointerVal(void** val)
		{
			*(void**)m_val = val;
		}
		void						setData(void* pData)
		{
			m_data = pData;
		}
		void*						getData()
		{
			return m_data;
		}

	private:

		PropType					m_type;
		std::wstring				m_name;
		void*						m_val;
		void*						m_data;
	};

	class PropertySet
	{
		template <typename T>
		struct PropTypeId
		{
			static Property::PropType			m_type;
		};
	public:
		PropertySet(const std::wstring& name);
		virtual ~PropertySet(void);

		bool								addProperty(const Property& p);
		unsigned long						getPropertyCount();
		Property*							getProperty(int iProp);

		template<typename T>
		bool								registerProperty(const wchar_t* szName, T* value)
		{
			Property::PropType type = PropTypeId<T>::m_type;
			if(type == Property::type_unknown)
			{
				return false;
			}

			Property prop(szName, type, value);
			m_props.push_back(prop);
			m_nameTable[szName] = m_props.size() - 1;

			return true;
		}

		Property*							getProperty(const wchar_t* szName);
		void								clearProperties();

		bool								hasProperty(const wchar_t* szName);

		const std::wstring&					getName(){return m_name;}
	private:
		std::vector<Property>				m_props;

		std::map<const wchar_t*, size_t>	m_nameTable;

		std::wstring						m_name;
	};

#endif

	template <typename T>
	Property::PropType PropTypeId<T>::m_type = Property::type_unknown;
	template <>
	Property::PropType PropTypeId<bool>::m_type = Property::type_bool;
	template <>
	Property::PropType PropTypeId<int>::m_type = Property::type_int;
	template <>
	Property::PropType PropTypeId<float>::m_type = Property::type_float;
	template <>
	Property::PropType PropTypeId<std::wstring>::m_type = Property::type_string;
	template <>
	Property::PropType PropTypeId<void*>::m_type = Property::type_pointer;
}
