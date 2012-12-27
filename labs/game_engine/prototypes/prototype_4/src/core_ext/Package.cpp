#include "core_ext_pch.h"
#include "Package.h"
#include "core\ext\MeshData.h"
#include "core\ext\MeshRenderer.h"
#include "core\ext\PropertyManager.h"
#include "core\ext\WorldMeshRenderer.h"
#include "core\ext\Light_Dir.h"
#include "core\ext\Light_Point.h"
#include "core\ext\Light_Spot.h"
#include "core\ext\Light_Sky.h"

EXPORT_C_API engine::ExtPackage* CreatePackage(engine::CoreApiPtr pCore)
{
	return new engine::Package(pCore);
}


EXPORT_C_API void DestroyPackage(engine::ExtPackage* pPackage)
{
	delete (engine::Package*)pPackage;
}



namespace engine
{
	CoreApiPtr					Package::s_pCore;

	Package::Package(CoreApiPtr pCore)
	{
		s_pCore = pCore;

		RegisterClasses();
	}
	void Package::RegisterClasses()
	{
		m_classes.push_back(ComponentClass(L"MeshData",
					L"Mesh",
					L"Mesh Data",
					&Package::Create_MeshData));

		m_classes.push_back(ComponentClass(L"MeshRenderer",
					L"Mesh",
					L"Mesh Renderer",
					&Package::Create_MeshRenderer));

		m_classes.push_back(ComponentClass(L"PropertyManager",
					L"Misc",
					L"Property Manager",
					&Package::Create_PropertyManager));

		/*m_classes.push_back(ComponentClass(L"WorldMeshRenderer",
					L"Mesh",
					L"World Mesh Renderer",
					&Package::Create_WorldMeshRenderer));
					*/

		m_classes.push_back(ComponentClass(L"DirectionalLight",
					L"Rendering",
					L"Directional Light",
					&Package::Create_DirectionalLight));

		m_classes.push_back(ComponentClass(L"PointLight",
					L"Rendering",
					L"Point Light",
					&Package::Create_PointLight));

		m_classes.push_back(ComponentClass(L"SpotLight",
					L"Rendering",
					L"Spot Light",
					&Package::Create_SpotLight));

		m_classes.push_back(ComponentClass(L"SkyLight",
					L"Rendering",
					L"Sky Light",
					&Package::Create_SkyLight));


	}

	Package::~Package(void)
	{
		s_pCore.reset();
	}
	CoreApiPtr Package::GetCoreApi()
	{
		return s_pCore;
	}
	Allocator* Package::GetAllocator()
	{
		return s_pCore->GetAllocator();
	}

	std::wstring Package::GetPackageName()
	{
		return L"core_ext_package";
	}
	
	int Package::GetClassCount()
	{
		return (int)m_classes.size();
	}
	Package::ComponentClass* Package::GetClassByIndex(int index)
	{
		return &m_classes[index];
	}

	GameObjectComponentPtr Package::Create_MeshData(GameObjectManagerPtr pManager)
	{
		return GetAllocator()->AllocObject<MeshData, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr Package::Create_MeshRenderer(GameObjectManagerPtr pManager)
	{
		return GetAllocator()->AllocObject<MeshRenderer, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr Package::Create_PropertyManager(GameObjectManagerPtr pManager)
	{
		return GetAllocator()->AllocObject<PropertyManager, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr Package::Create_WorldMeshRenderer(GameObjectManagerPtr pManager)
	{
		return GetAllocator()->AllocObject<WorldMeshRenderer, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr Package::Create_DirectionalLight(GameObjectManagerPtr pManager)
	{
		return GetAllocator()->AllocObject<Light_Dir, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr Package::Create_PointLight(GameObjectManagerPtr pManager)
	{
		return GetAllocator()->AllocObject<Light_Point, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr Package::Create_SpotLight(GameObjectManagerPtr pManager)
	{
		return GetAllocator()->AllocObject<Light_Spot, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr Package::Create_SkyLight(GameObjectManagerPtr pManager)
	{
		return GetAllocator()->AllocObject<Light_Sky, GameObjectManagerPtr>(pManager);
	}
}

