#pragma once

#include "core\ExtPackage.h"

namespace engine
{
	class Package : public ExtPackage
	{
	public:
		Package(CoreApiPtr pCore);
		virtual ~Package(void);

		std::wstring						GetPackageName();
		int									GetClassCount();
		ComponentClass*						GetClassByIndex(int index);


		static CoreApiPtr					GetCoreApi();
		static Allocator*					GetAllocator();

	private:
		void								RegisterClasses();

		static GameObjectComponentPtr		Create_MeshData(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_MeshRenderer(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_PropertyManager(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_WorldMeshRenderer(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_DirectionalLight(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_PointLight(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_SpotLight(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_SkyLight(GameObjectManagerPtr pManager);

	private:
		static CoreApiPtr					s_pCore;

		std::vector<ComponentClass>			m_classes;
	};
}
