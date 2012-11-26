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
	
	AppContext::GetCoreApi()->GetSysGraphics()->SetClearColor(math::Color4(0.2, 0.2, 0.4, 1.0f));
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
void Renderer::CreateGridMesh()
{

}