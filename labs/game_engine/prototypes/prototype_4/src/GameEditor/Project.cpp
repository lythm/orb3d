#include "StdAfx.h"
#include "Project.h"
#include <afxconv.h>
#include "AppContext.h"


Project::Project(void)
{
	m_objNo	= 0;
}


Project::~Project(void)
{
}

bool Project::New()
{
	if(AppContext::GetRenderSystem()->GetLightCount() == 0)
	{
		AddDefaultLight();
	}

	AppContext::UpdateObjectView();
	return true;
}
bool Project::Load(const _TCHAR* filename)
{
	m_filePath = filename;

	USES_CONVERSION;

	TiXmlDocument doc;

	doc.LoadFile(W2A(filename));


	if(AppContext::GetRenderSystem()->GetLightCount() == 0)
	{
		AddDefaultLight();
	}

	AppContext::UpdateObjectView();
	return true;
}
bool Project::Save(const _TCHAR* filename)
{
	TiXmlDocument doc;

	USES_CONVERSION;
	doc.InsertEndChild(TiXmlElement("Project"));

	if(false == doc.SaveFile(W2A(filename)))
	{
		return false;
	}
	
	m_filePath = filename;
	return true;
}
void Project::Close()
{
	AppContext::GetCoreApi()->GetRoot()->Clear();
}

void Project::AddDefaultLight()
{
	using namespace engine;
	using namespace engine;

	GameObjectPtr pObj = AppContext::CreateGameObject(L"Default Light");
		
	Light_SkyPtr pLight = boost::shared_dynamic_cast<Light_Sky>(AppContext::CreateGameObjectComponent(L"SkyLight"));
	pObj->AddComponent(pLight);
	pObj->SetTranslation(1, 1, 1);
	pObj->LookAt(math::Vector3(0, 0, 0));

}
void Project::CreateObject_FromTemplate_Sphere()
{
	using namespace engine;

	Sys_GraphicsPtr pGraphics = AppContext::GetSysGraphics();


	GameObjectPtr pObj = CreateObject(L"Sphere");

	MaterialPtr pMaterial = pGraphics->CreateMaterialFromFile("./assets/material/editor_shape.fx");
	pMaterial->SelectTechByName("dr_render_gbuffer");

	MeshPtr pMesh = MeshUtil::CreateSphere(1, 20, 20, pMaterial);

	RenderSystemPtr pRS = AppContext::GetCoreApi()->GetRenderSystem();

	MeshDataPtr pMD = boost::shared_dynamic_cast<MeshData>(AppContext::CreateGameObjectComponent(L"MeshData"));
	pMD->SetMesh(pMesh);

	pObj->AddComponent(pMD);

	MeshRendererPtr pMR = boost::shared_dynamic_cast<MeshRenderer>(AppContext::CreateGameObjectComponent(L"MeshRenderer"));
	pObj->AddComponent(pMR);
}

void Project::CreateObject_FromTemplate_Cone()
{
	using namespace engine;

	Sys_GraphicsPtr pGraphics = AppContext::GetSysGraphics();


	GameObjectPtr pObj = CreateObject(L"Cone");

	MaterialPtr pMaterial = pGraphics->CreateMaterialFromFile("./assets/material/editor_shape.fx");
	pMaterial->SelectTechByName("dr_render_gbuffer");

	MeshPtr pMesh = MeshUtil::CreateCone(1, 30, 99, pMaterial);

	RenderSystemPtr pRS = AppContext::GetCoreApi()->GetRenderSystem();

	MeshDataPtr pMD = boost::shared_dynamic_cast<MeshData>(AppContext::CreateGameObjectComponent(L"MeshData"));
	pMD->SetMesh(pMesh);

	pObj->AddComponent(pMD);

	MeshRendererPtr pMR = boost::shared_dynamic_cast<MeshRenderer>(AppContext::CreateGameObjectComponent(L"MeshRenderer"));
	pObj->AddComponent(pMR);
}
void Project::CreateObject_FromTemplate_Plane()
{
	using namespace engine;

	GameObjectPtr pObj = CreateObject(L"Plane");

	Sys_GraphicsPtr pGraphics = AppContext::GetSysGraphics();

	MaterialPtr pMaterial = pGraphics->CreateMaterialFromFile("./assets/material/editor_shape.fx");
	MeshPtr pMesh = MeshUtil::CreatePlane(100, pMaterial);

	RenderSystemPtr pRS = AppContext::GetCoreApi()->GetRenderSystem();

	MeshDataPtr pMD = boost::shared_dynamic_cast<MeshData>(AppContext::CreateGameObjectComponent(L"MeshData"));
	pMD->SetMesh(pMesh);

	pObj->AddComponent(pMD);

	MeshRendererPtr pMR = boost::shared_dynamic_cast<MeshRenderer>(AppContext::CreateGameObjectComponent(L"MeshRenderer"));
	pObj->AddComponent(pMR);
}
void Project::CreateObject_FromTemplate_Cube()
{
	using namespace engine;

	GameObjectPtr pObj = CreateObject(L"Cube");

	Sys_GraphicsPtr pGraphics = AppContext::GetSysGraphics();

	MaterialPtr pMaterial = pGraphics->CreateMaterialFromFile("./assets/material/editor_shape.fx");
	MeshPtr pMesh = MeshUtil::CreateCube(2, pMaterial);

	RenderSystemPtr pRS = AppContext::GetCoreApi()->GetRenderSystem();

	MeshDataPtr pMD = boost::shared_dynamic_cast<MeshData>(AppContext::CreateGameObjectComponent(L"MeshData"));
	pMD->SetMesh(pMesh);

	pObj->AddComponent(pMD);

	MeshRendererPtr pMR = boost::shared_dynamic_cast<MeshRenderer>(AppContext::CreateGameObjectComponent(L"MeshRenderer"));
	pObj->AddComponent(pMR);

}
void Project::CreateObject_Empty()
{
	using namespace engine;
	GameObjectPtr pObj = CreateObject(L"GameObject");
}
engine::GameObjectPtr Project::CreateObject(const std::wstring& name)
{
	using namespace engine;

	CString full_name;

	full_name.Format(L"%s-%d", name.c_str(), m_objNo);
	
	GameObjectPtr pObj = AppContext::CreateGameObject(full_name.GetString());

	m_objNo++;
	return pObj;
}
void Project::CreateObject_FromTemplate_DirLight()
{
	using namespace engine;
	
	GameObjectPtr pObj = CreateObject(L"Directional Light");
		
	Light_DirPtr pLight = boost::shared_dynamic_cast<Light_Dir>(AppContext::CreateGameObjectComponent(L"DirectionalLight"));
	pObj->AddComponent(pLight);
}


void Project::CreateObject_FromTemplate_PointLight()
{
	using namespace engine;
	
	GameObjectPtr pObj = CreateObject(L"Point Light");
		
	Light_PointPtr pLight = boost::shared_dynamic_cast<Light_Point>(AppContext::CreateGameObjectComponent(L"PointLight"));
	pObj->AddComponent(pLight);
	
}


void Project::CreateObject_FromTemplate_SpotLight()
{
	using namespace engine;
	
	GameObjectPtr pObj = CreateObject(L"Spot Light");
		
	Light_SpotPtr pLight = boost::shared_dynamic_cast<Light_Spot>(AppContext::CreateGameObjectComponent(L"SpotLight"));
	pObj->AddComponent(pLight);

}
void Project::CreateObject_FromTemplate_SkyLight()
{
	using namespace engine;
	
	GameObjectPtr pObj = CreateObject(L"Sky Light");
		
	Light_SkyPtr pLight = boost::shared_dynamic_cast<Light_Sky>(AppContext::CreateGameObjectComponent(L"SkyLight"));
	pObj->AddComponent(pLight);

}