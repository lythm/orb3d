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
	bool Package::RegisterPacket(GameObjectManager* pManager)
	{
		pManager->RegisterComponent(L"PropertyManager", PropertyManager::CreateComponent);
		pManager->RegisterComponent(L"MeshData", MeshData::CreateComponent);
		pManager->RegisterComponent(L"MeshRenderer", MeshRenderer::CreateComponent);
		pManager->RegisterComponent(L"WorldMeshRenderer", WorldMeshRenderer::CreateComponent);
		pManager->RegisterComponent(L"DirectionalLight", Light_Dir::CreateComponent);
		pManager->RegisterComponent(L"PointLight", Light_Point::CreateComponent);
		pManager->RegisterComponent(L"SpotLight", Light_Spot::CreateComponent);
		pManager->RegisterComponent(L"SkyLight", Light_Sky::CreateComponent);
		
		return true;
	}
}

