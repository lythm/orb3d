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
	m_pGrid = boost::shared_ptr<GridMesh>(new GridMesh());

	if(false == m_pGrid->Init(300, 10))
	{
		return false;
	}

	using namespace math;
	using namespace engine;

	m_pCamera = EditorCameraPtr(new EditorCamera);

	ResetViewPort(vpw, vph);

	m_pCamera->LookAtLH(Vector3(0, 150, -150), Vector3(0, 0, 0), Vector3(0, 1, 0));
	
	m_pCamera->Update();
	
	return true;
}
void Renderer::ResetViewPort(int vpw, int vph)
{
	m_pCamera->SetViewPort(vpw, vph);

	using namespace math;
	using namespace engine;
	float aspect = vpw /vph;
	m_pCamera->PerspectiveFovLH(1.0f/ 4.0f * MATH_PI, aspect, 0.001, 10000000);

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