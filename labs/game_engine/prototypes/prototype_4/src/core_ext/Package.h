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

		static GameObjectComponentPtr		Create_MeshData();
		static GameObjectComponentPtr		Create_MeshRenderer();
		static GameObjectComponentPtr		Create_PropertyManager();
		static GameObjectComponentPtr		Create_WorldMeshRenderer();
		static GameObjectComponentPtr		Create_DirectionalLight();
		static GameObjectComponentPtr		Create_PointLight();
		static GameObjectComponentPtr		Create_SpotLight();
		static GameObjectComponentPtr		Create_SkyLight();

	private:
		static CoreApiPtr					s_pCore;

		std::vector<ComponentClass>			m_classes;
	};
}
