#pragma once

namespace ld3d
{
	class GameObjectTemplate;

	class ExtPackage
	{
	public:

		struct ComponentClass
		{
			ComponentClass(const std::wstring& name, 
								const std::wstring& catalog, 
								const std::wstring& desc, 
								boost::function<GameObjectComponentPtr (GameObjectManagerPtr)> creator,
								const std::vector<std::wstring>& deps = std::vector<std::wstring>(),
								bool bExclusive = true)
			{
				m_name						= name;
				m_catalog					= catalog;
				m_desc						= desc;
				m_creator					= creator;
				m_deps						= deps;
				m_bExclusive				= bExclusive;
			}
			ComponentClass()
			{

			}
		
			std::wstring									m_name;
			std::wstring									m_catalog;
			std::wstring									m_desc;
			boost::function<GameObjectComponentPtr (GameObjectManagerPtr)>		m_creator;

			std::vector<std::wstring>						m_deps;
			bool											m_bExclusive;
		};

		virtual const wchar_t*								GetPackageName()								= 0;
		virtual int											GetClassCount()									= 0;
		virtual ComponentClass*								GetClassByIndex(int index)						= 0;

		virtual int											GetTemplateCount(){return 0;}
		virtual GameObjectTemplate*							GetTemplateByIndex(int index){return nullptr;}

		virtual void										Release()										= 0;

	protected:
		ExtPackage(void){}
		virtual ~ExtPackage(void){}
	private:

	};
}
