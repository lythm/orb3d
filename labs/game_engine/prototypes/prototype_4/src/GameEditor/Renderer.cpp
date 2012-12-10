#include "StdAfx.h"
#include "Renderer.h"
#include "GridMesh.h"
#include "AppContext.h"
#include "EditorCamera.h"


Renderer::Renderer(void)
{
}


Renderer::~Renderer(void)
{
}
bool Renderer::Initialize(int vpw, int vph)
{
	using namespace math;
	using namespace engine;

	m_pGrid = boost::shared_ptr<GridMesh>(new GridMesh());

	if(false == m_pGrid->Init(300, 10))
	{
		return false;
	}
	m_pCamera = EditorCameraPtr(new EditorCamera);
	m_pCamera->SetViewPort(vpw, vph);

	m_pCamera->Init();
	m_pCamera->Update();
	
	return true;
}
void Renderer::Resize(int cx, int cy)
{
	engine::Sys_GraphicsPtr pGraphics = AppContext::GetSysGraphics();
	if(pGraphics != NULL)
	{
		if(cx != 0 && cy != 0)
		{
			pGraphics->ResizeFrameBuffer(cx, cy);
			pGraphics->SetRenderTarget(engine::RenderTargetPtr());
		}
	}

	m_pCamera->SetViewPort(cx, cy);
}
void Renderer::Release()
{
	if(m_pGrid)
	{
		m_pGrid->Release();
		m_pGrid.reset();
	}
}
void Renderer::Render()
{
	AppContext::GetCoreApi()->Update();

	AppContext::GetCoreApi()->AddRenderData(m_pGrid);

	m_pCamera->Update();

	AppContext::GetCoreApi()->Render();
	AppContext::GetCoreApi()->ClearRenderQueue();

	AppContext::GetCoreApi()->Present();

}
void Renderer::UpdateSemantics()
{

}
void Renderer::OnMouseMove(UINT nFlags, CPoint point)
{
	m_pCamera->OnMouseMove(nFlags, point);

}
void Renderer::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	m_pCamera->OnMouseWheel(nFlags, zDelta, pt);
}
void Renderer::OnMouseRButtonDown(UINT nFlags, CPoint point)
{
	m_pCamera->OnMouseRButtonDown(nFlags, point);
}
void Renderer::OnMouseRButtonUp(UINT nFlags, CPoint point)
{
	m_pCamera->OnMouseRButtonUp(nFlags, point);
}

void Renderer::CreateObject_FromTemplate_Sphere()
{
	using namespace engine;

	Sys_GraphicsPtr pGraphics = AppContext::GetSysGraphics();


	GameObjectPtr pObj = AppContext::GetCoreApi()->CreateGameObject(L"Sphere");

	MaterialPtr pMaterial = pGraphics->CreateMaterialFromFile("./assets/gfx/editor_sphere.fx");

	MeshPtr pMesh = MeshUtil::CreateSphere(20, 100, 100, pMaterial);

	RenderSystemPtr pRS = AppContext::GetCoreApi()->GetRenderSystem();

	MeshDataPtr pMD = boost::shared_dynamic_cast<object_component::MeshData>(AppContext::GetCoreApi()->CreateGameObjectComponent(L"MeshData"));
	pMD->SetMesh(pMesh);

	pObj->AddComponent(pMD);

	MeshRendererPtr pMR = boost::shared_dynamic_cast<object_component::MeshRenderer>(AppContext::GetCoreApi()->CreateGameObjectComponent(L"MeshRenderer"));
	pMR->SetRenderSystem(pRS);
	pObj->AddComponent(pMR);
}
void Renderer::CreateObject_FromTemplate_Cube()
{
	using namespace engine;

	GameObjectPtr pObj = AppContext::GetCoreApi()->CreateGameObject(L"Cube");

	Sys_GraphicsPtr pGraphics = AppContext::GetSysGraphics();

	MaterialPtr pMaterial = pGraphics->CreateMaterialFromFile("./assets/gfx/editor_cube.fx");
	MeshPtr pMesh = MeshUtil::CreateCube(20, pMaterial);

	RenderSystemPtr pRS = AppContext::GetCoreApi()->GetRenderSystem();

	MeshDataPtr pMD = boost::shared_dynamic_cast<object_component::MeshData>(AppContext::GetCoreApi()->CreateGameObjectComponent(L"MeshData"));
	pMD->SetMesh(pMesh);

	pObj->AddComponent(pMD);

	MeshRendererPtr pMR = boost::shared_dynamic_cast<object_component::MeshRenderer>(AppContext::GetCoreApi()->CreateGameObjectComponent(L"MeshRenderer"));
	pMR->SetRenderSystem(pRS);
	pObj->AddComponent(pMR);

}
void Renderer::CreateObject_Empty()
{
	using namespace engine;
	GameObjectPtr pObj = AppContext::GetCoreApi()->CreateGameObject(L"GameObject");
}
