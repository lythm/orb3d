#pragma once

#include "core\ExtPackage.h"

namespace ld3d
{
	class CorePackage : public ExtPackage
	{
	public:
		CorePackage(CoreApiPtr pCore);
		virtual ~CorePackage(void);

		const wchar_t*						GetPackageName();
		int									GetClassCount();
		ComponentClass*						GetClassByIndex(int index);


		int									GetTemplateCount();
		GameObjectTemplate*					GetTemplateByIndex(int index);


		void								Release();
	private:
		void								RegisterClasses();
		void								RegisterTemplates();

		static GameObjectComponentPtr		Create_SkyBox(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_MeshData(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_MeshRenderer(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_PropertyManager(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_WorldMeshRenderer(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_DirectionalLight(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_PointLight(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_SpotLight(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_SkyLight(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_Camera(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_Sky(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_PostEffectList(GameObjectManagerPtr pManager);

		static GameObjectComponentPtr		Create_LuaBehavior(GameObjectManagerPtr pManager);

		static GameObjectComponentPtr		Create_SoundEmitter(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_SoundListener(GameObjectManagerPtr pManager);

	private:
		CoreApiPtr							m_pCore;

		std::vector<ComponentClass>			m_classes;

		std::vector<GameObjectTemplate*>	m_tpls;

		
	};
}
