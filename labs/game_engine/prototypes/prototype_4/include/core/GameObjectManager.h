#pragma once

#include "core\ExtPackage.h"

#include <boost\enable_shared_from_this.hpp>

namespace engine
{
	class EXPORT_CLASS GameObjectManager : public boost::enable_shared_from_this<GameObjectManager>
	{
		class PackageMod
		{
		public:
			PackageMod();
			typedef ExtPackage*					(*Fn_CreatePackage)(CoreApiPtr pCore);
			typedef void						(*Fn_DestroyPackage)(ExtPackage*);

			bool								load_package(const wchar_t* file, CoreApiPtr pCore);
			void								delete_package();

			ExtPackage*							GetPackage();

		private:
			ExtPackage*							m_pPackage;
			HMODULE								m_hLib;
			std::wstring						m_file;
		};

	public:
		GameObjectManager(void);
		virtual ~GameObjectManager(void);

		bool							Initialize(CoreApiPtr pCore);
		void							Release();

		bool							LoadPackage(const std::wstring& name);

		GameObjectPtr					CreateGameObject(const std::wstring& name);
		GameObjectPtr					CreateObjectFromTemplate(const std::string& tpl);
		
		void							RegisterObject();

		void							UpdateObjects();

		GameObjectPtr					GetRoot();
		
		GameObjectComponentPtr			CreateComponent(const std::wstring& name);

		void							WalkObjectTree();

		int								GetPackageCount();
		ExtPackage*						GetPackageByIndex(int index);

		bool							RegisterPackage(ExtPackage* pPack);
		bool							RegisterComponentClass(ExtPackage::ComponentClass* c);

		RenderSystemPtr					GetRenderSystem();
	private:

		void							ReleaseAllObject();

		void							_tree_walk(GameObject* pObj);

	private:
		GameObjectPtr					m_pRoot;

		boost::unordered_map<std::string, GameObjectTemplatePtr>			m_templates;
		boost::unordered_map<std::wstring, ExtPackage::ComponentClass*>		m_componentClasses;

		std::vector<PackageMod>			m_packages;
		CoreApiPtr						m_pCore;
	};
}
