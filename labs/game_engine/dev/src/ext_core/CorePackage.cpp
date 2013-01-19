#include "core_ext_pch.h"
#include "CorePackage.h"
#include "core\ext\MeshData.h"
#include "core\ext\MeshRenderer.h"
#include "core\ext\PropertyManager.h"
#include "core\ext\WorldMeshRenderer.h"
#include "core\ext\Light_Dir.h"
#include "core\ext\Light_Point.h"
#include "core\ext\Light_Spot.h"
#include "core\ext\Light_Sky.h"
#include "core\ext\SkyBox.h"
#include "core\ext\CameraData.h"
#include "core\ext\Sky.h"
#include "core\ext\PostEffectList.h"
#include "core\ext\LuaBehavior.h"
#include "core\ext\SoundEmitter.h"
#include "core\ext\SoundListener.h"



#include "Tpl_Cube.h"
#include "Tpl_Plane.h"
#include "Tpl_Sphere.h"
#include "Tpl_Cone.h"
#include "Tpl_PointLight.h"
#include "Tpl_SkyLight.h"
#include "Tpl_SpotLight.h"
#include "Tpl_DirLight.h"
#include "Tpl_Camera.h"

EXPORT_C_API ld3d::ExtPackage* CreatePackage(ld3d::CoreApiPtr pCore)
{
	return new ld3d::CorePackage(pCore);
}


EXPORT_C_API void DestroyPackage(ld3d::ExtPackage* pPackage)
{
	delete (ld3d::CorePackage*)pPackage;
}



namespace ld3d
{
	CorePackage::CorePackage(CoreApiPtr pCore)
	{
		m_pCore = pCore;

		RegisterClasses();

		RegisterTemplates();
	}
	CorePackage::~CorePackage(void)
	{
		m_pCore.reset();
	}
	void CorePackage::RegisterTemplates()
	{
		GameObjectTemplate* pTpl = new Tpl_Cube(m_pCore->GetGameObjectManager(), L"Cube");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_Plane(m_pCore->GetGameObjectManager(), L"Plane");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_Sphere(m_pCore->GetGameObjectManager(), L"Sphere");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_Cone(m_pCore->GetGameObjectManager(), L"Cone");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_PointLight(m_pCore->GetGameObjectManager(), L"PointLight");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_SpotLight(m_pCore->GetGameObjectManager(), L"SpotLight");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_DirLight(m_pCore->GetGameObjectManager(), L"DirectionalLight");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_SkyLight(m_pCore->GetGameObjectManager(), L"SkyLight");
		m_tpls.push_back(pTpl);

		pTpl = new Tpl_Camera(m_pCore->GetGameObjectManager(), L"Camera");
		m_tpls.push_back(pTpl);

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

		m_classes.push_back(ComponentClass(L"LuaBehavior",
					L"Script",
					L"Lua script Behavior",
					&CorePackage::Create_LuaBehavior));

		m_classes.push_back(ComponentClass(L"SoundEmitter",
					L"Sound",
					L"Sound Emitter",
					&CorePackage::Create_SoundEmitter));

		m_classes.push_back(ComponentClass(L"SoundListener",
					L"Sound",
					L"Sound Listener",
					&CorePackage::Create_SoundListener));

	}

	
	void CorePackage::Release()
	{
		m_classes.clear();

		for(size_t i = 0; i < m_tpls.size(); ++i)
		{
			m_tpls[i]->Release();
			delete m_tpls[i];
		}
		m_tpls.clear();
	}
	const wchar_t* CorePackage::GetPackageName()
	{
		return L"Core";
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
		return pManager->GetAllocator()->AllocObject<CameraData, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_Sky(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<Sky, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_PostEffectList(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<PostEffectList, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_LuaBehavior(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<LuaBehavior, GameObjectManagerPtr>(pManager);
	}

	int	CorePackage::GetTemplateCount()
	{
		return (int)m_tpls.size();
	}
	GameObjectTemplate* CorePackage::GetTemplateByIndex(int index)
	{
		return m_tpls[index];
	}

	GameObjectComponentPtr CorePackage::Create_SoundEmitter(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<SoundEmitter, GameObjectManagerPtr>(pManager);
	}
	GameObjectComponentPtr CorePackage::Create_SoundListener(GameObjectManagerPtr pManager)
	{
		return pManager->GetAllocator()->AllocObject<SoundListener, GameObjectManagerPtr>(pManager);
	}
}

