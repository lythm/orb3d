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
	ResetViewPort(vpw, vph);

	m_pCamera->Init();
	m_pCamera->Update();
	
	return true;
}
void Renderer::ResetViewPort(int vpw, int vph)
{
	m_pCamera->SetViewPort(vpw, vph);

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
engine::MeshPtr Renderer::CreateCube(int size)
{
	using namespace engine;

	Sys_GraphicsPtr pGraphics = AppContext::GetSysGraphics();

	MeshPtr pMesh = MeshPtr(new Mesh);

	struct Vertex
	{
		math::Vector3			pos;
	};

	Vertex verts[] = 
	{
		{ math::Vector3(10, 10, -10)},
		{ math::Vector3(10, -10, -10)},
		{ math::Vector3(-10, -10, -10)},
		{ math::Vector3(-10, 10, -10)},


		{ math::Vector3(10, 10, 10)},
		{ math::Vector3(10, -10, 10)},
		{ math::Vector3(-10, -10, 10)},
		{ math::Vector3(-10, 10, 10)},
	};

	uint16 indice[] = 
	{
		0, 1, 2,
		0, 2, 3,

		4, 6, 5,
		4, 7, 6,

		0, 3, 4,
		4, 3, 7,

		1, 5, 6,
		1, 6, 2,

		0, 4, 5,
		0, 5, 1,

		3, 2, 6,
		3, 6, 7,
	};

	VertexElement vf[] = 
	{
		VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
	};

	std::vector<MaterialPtr> pMatList;
	
	MaterialPtr pMaterial = pGraphics->CreateMaterialFromFile("./assets/gfx/editor_cube.fx");
	pMaterial->SetVertexFormat(vf, 1);
	pMatList.push_back(pMaterial);

	pMesh->Create(36 * sizeof(uint16), indice, sizeof(Vertex) * 8, verts, pMatList);

	SubMeshPtr pSub = SubMeshPtr(new SubMesh());	
	pSub->Create(pMesh, 0, 36, 0, 8, sizeof(Vertex), 0, 12);
	pMesh->AddSubMesh(pSub);

	return pMesh;
}
void Renderer::CreateObject_FromTemplate_Cube()
{
	using namespace engine;

	GameObjectPtr pObj = AppContext::GetCoreApi()->CreateGameObject(L"Cube");

	MeshPtr pMesh = MeshPtr(new Mesh());

	RenderSystemPtr pRS = AppContext::GetCoreApi()->GetRenderSystem();

	MeshDataPtr pMD = boost::shared_dynamic_cast<object_component::MeshData>(AppContext::GetCoreApi()->CreateGameObjectComponent(L"MeshData"));
	pMD->SetMesh(CreateCube(100));

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
