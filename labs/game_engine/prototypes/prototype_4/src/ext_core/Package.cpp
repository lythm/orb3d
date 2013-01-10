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
#include "core\ext\SkyBox.h"
#include "core\ext\Camera.h"
#include "core\ext\Sky.h"
#include "core\ext\PostEffectList.h"

EXPORT_C_API engine::ExtPackage* CreatePackage(engine::CoreApiPtr pCore)
{
	return new engine::CorePackage(pCore);
}


EXPORT_C_API void DestroyPackage(engine::ExtPackage* pPackage)
{
	delete (engine::CorePackage*)pPackage;
}



namespace engine
{
	CorePackage::CorePackage(CoreApiPtr pCore)
	{
		m_pCore = pCore;

		RegisterClasses();
	}
	void CorePackage::RegisterClasses()
	{
		m_classes.push_back(ComponentClass(L"MeshData",
					L"Mesh",
					L"Mesh Data",
					&CorePackage::Create_MeshData));

		m_classes.push_back(ComponentClass(L"MeshRenderer",
					L"Mesh",
					L"Mesh Renderer",
					&CorePackage::Create_MeshRenderer));

		m_classes.push_back(ComponentClass(L"PropertyManager",
					L"Misc",
					L"Property Manager",
					&CorePackage::Create_PropertyManager));

		/*m_classes.push_back(ComponentClass(L"WorldMeshRenderer",
					L"Mesh",
					L"World Mesh Renderer",
					&Package::Create_WorldMeshRenderer));
					*/

		m_classes.push_back(ComponentClass(L"DirectionalLight",
					L"Light",
					L"Directional Light",
					&CorePackage::Create_DirectionalLight));

		m_classes.push_back(ComponentClass(L"PointLight",
					L"Light",
					L"Point Light",
					&CorePackage::Create_PointLight));

		m_classes.push_back(ComponentClass(L"SpotLight",
					L"Light",
					L"Spot Light",
					&CorePackage::Create_SpotLight));

		m_classes.push_back(ComponentClass(L"SkyLight",
					L"Light",
					L"Sky Light",
					&CorePackage::Create_SkyLight));

		m_classes.push_back(ComponentClass(L"SkyBox",
					L"Camera",
					L"SkyBox",
					&CorePackage::Create_SkyBox));

		m_classes.push_back(ComponentClass(L"Camera",
					L"Camera",
					L"Camera",
					&CorePackage::Create_Camera));

		m_classes.push_back(ComponentClass(L"Sky",
					L"Rendering",
					L"Sky",
					&CorePackage::Create_Sky));

		m_classes.push_back(ComponentClass(L"PostEffectList",
					L"Camera",
					L"PostEffectList",
					&CorePackage::Create_PostEffectList));


	}

	CorePackage::~CorePackage(void)
	{
		m_pCore.reset();
	}
	
	std::wstring CorePackage::GetPackageName()
	{
		return L"core_ext_package";
	}
	
	int CorePackage::GetClassCount()
	{
		return (int)m_classes.size();
	}
	CorePackage::ComponentClass* CorePackage::GetClassByIndex(int index)
	{
		return &m_classes[index];
	}

	GameObjectComponentPtr CorePackage::Create_MeshData(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<MeshData, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_MeshRenderer(GameObjectManagerPtr pManager)
	{
		return pManager-> GetAllocator()->AllocObject<MeshRenderer, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_PropertyManager(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<PropertyManager, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_WorldMeshRenderer(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<WorldMeshRenderer, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_DirectionalLight(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<Light_Dir, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_PointLight(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<Light_Point, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_SpotLight(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<Light_Spot, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_SkyLight(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<Light_Sky, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_SkyBox(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<SkyBox, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_Camera(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<Camera, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_Sky(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<Sky, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_PostEffectList(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<PostEffectList, GameObjectManagerPtr>(pManager);
	}
}

