#include "StdAfx.h"
#include "Renderer.h"
#include "GridMesh.h"
#include "AppContext.h"


Renderer::Renderer(void)
{
}


Renderer::~Renderer(void)
{
}
bool Renderer::Initialize()
{
	m_pGrid = boost::shared_ptr<GridMesh>(new GridMesh());

	if(false == m_pGrid->Init())
	{
		return false;
	}
	
	using namespace math;
	using namespace engine;
	Matrix44 view, world, proj;

	float aspect = float(AppContext::GetRTViewWidth()) / float(AppContext::GetRTViewHeight());
	aspect = 4.0f / 3.0f;

	proj = MatrixPerspectiveFovLH(3.0f/ 4.0f * MATH_PI, aspect, 0.001, 10000000);
	view = MatrixLookAtLH(Vector3(0, 50, -50), Vector3(0, 0, 0), Vector3(0, 1, 0));
	world.MakeIdentity();

	RenderSystemPtr pRS = AppContext::GetCoreApi()->GetRenderSystem();

	pRS->SetViewMatrix(view);
	pRS->SetProjMatrix(proj);

	return true;
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

	AppContext::GetCoreApi()->Render();

	AppContext::GetCoreApi()->ClearRenderQueue();
}
