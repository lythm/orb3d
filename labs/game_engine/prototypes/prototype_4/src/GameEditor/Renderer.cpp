#include "StdAfx.h"
#include "Renderer.h"
#include "GridMesh.h"
#include "AppContext.h"
#include "EditorCamera.h"


Renderer::Renderer(void)
{
	m_bShowGrid			= true;
}


Renderer::~Renderer(void)
{
}
bool Renderer::Initialize(int vpw, int vph)
{
	using namespace math;
	using namespace engine;

	m_pGrid = boost::shared_ptr<GridMesh>(new GridMesh());

	if(false == m_pGrid->Init(1000, 10))
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
			AppContext::GetCoreApi()->GetRenderSystem()->ResizeFrameBuffer(cx, cy);
			m_pCamera->SetViewPort(cx, cy);
		}
	}
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

	UpdateFPS();

	AppContext::GetCoreApi()->Update();

	m_bShowGrid ? AppContext::GetCoreApi()->AddRenderData(m_pGrid) : 0;

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


void Renderer::ShowGrid(bool bShow)
{
	m_bShowGrid = bShow;
}
bool Renderer::ShowingGrid()
{
	return m_bShowGrid;
}
void Renderer::OnMouseLButtonClick(UINT nFlags, CPoint point)
{
	AppContext::ClearObjectViewSelection();
	AppContext::UpdatePropGrid(engine::GameObjectPtr());
	AppContext::SetSelectedObject(engine::GameObjectPtr());
}
void Renderer::UpdateFPS()
{
	static int frame = 0;
	static int tick = GetTickCount();

	int dt = GetTickCount() - tick;

	if(dt > 500)
	{
		float fps = float(frame * 1000) / float(dt);
		AppContext::UpdateStatusBar_FPS(fps);
		tick = GetTickCount();
		frame = 0;
	}
	frame++;
}