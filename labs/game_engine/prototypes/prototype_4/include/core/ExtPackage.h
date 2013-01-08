#pragma once

namespace engine
{
	class ExtPackage
	{
	public:

		struct ComponentClass
		{
			ComponentClass(const std::wstring& name, const std::wstring& catalog, const std::wstring& desc, boost::function<GameObjectComponentPtr (GameObjectManagerPtr)> creator)
			{
				m_name						= name;
				m_catalog					= catalog;
				m_desc						= desc;
				m_creator					= creator;
			}
			ComponentClass()
			{

			}
		
			std::wstring									m_name;
			std::wstring									m_catalog;
			std::wstring									m_desc;
			boost::function<GameObjectComponentPtr (GameObjectManagerPtr)>		m_creator;

		};

		virtual std::wstring								GetPackageName()								= 0;
		virtual int											GetClassCount()									= 0;
		virtual ComponentClass*								GetClassByIndex(int index)						= 0;

		virtual int											GetTemplateCount(){return 0;}
		virtual GameObjectTemplatePtr						GetTemplateByIndex(int index){return GameObjectTemplatePtr();}

	protected:
		ExtPackage(void){}
		virtual ~ExtPackage(void){}
	private:

	};
}
