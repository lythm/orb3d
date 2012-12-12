#pragma once
#include <string>
#include <vector>
#include <map>

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


	template <typename T>
	Property::PropType PropertySet::PropTypeId<T>::m_type = Property::type_unknown;
	template <>
	Property::PropType PropertySet::PropTypeId<bool>::m_type = Property::type_bool;
	template <>
	Property::PropType PropertySet::PropTypeId<int>::m_type = Property::type_int;
	template <>
	Property::PropType PropertySet::PropTypeId<float>::m_type = Property::type_float;
	template <>
	Property::PropType PropertySet::PropTypeId<std::wstring>::m_type = Property::type_string;
	template <>
	Property::PropType PropertySet::PropTypeId<void*>::m_type = Property::type_pointer;
}
