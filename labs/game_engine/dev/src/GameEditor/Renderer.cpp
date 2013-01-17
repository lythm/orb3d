#include "StdAfx.h"
#include "Renderer.h"
#include "GridMesh.h"
#include "EditorCamera.h"
#include "Project.h"
#include "editor_utils.h"
#include "MainFrm.h"

Renderer::Renderer(void)
{
	m_bShowGrid			= true;
}


Renderer::~Renderer(void)
{
}
bool Renderer::Initialize(ld3d::CoreApiPtr pCore)
{
	using namespace math;
	using namespace ld3d;

	m_pCore = pCore;
	m_pRS = m_pCore->GetRenderSystem();

	m_pGrid = boost::shared_ptr<GridMesh>(new GridMesh());

	if(false == m_pGrid->Init(m_pCore, 1000, 10))
	{
		return false;
	}
	m_pCamera = EditorCameraPtr(new EditorCamera);
	
	int vpw = m_pCore->GetRenderSystem()->GetFrameBufferWidth();
	int vph = m_pCore->GetRenderSystem()->GetFrameBufferHeight();

	m_pCamera->SetViewPort(vpw, vph);

	m_pCamera->Init(pCore);
	m_pCamera->Update();
	
	
	return true;
}
void Renderer::Resize(int cx, int cy)
{
	if(m_pCore == nullptr)
	{
		return;
	}
	if(cx != 0 && cy != 0)
	{
		m_pCore->GetRenderSystem()->ResizeFrameBuffer(cx, cy);
		m_pCore->GetSysGraphics()->SetViewPort(0, 0, cx, cy);
		m_pCamera->SetViewPort(cx, cy);
	}
}
void Renderer::Release()
{
	if(m_pGrid)
	{
		m_pGrid->Release();
		m_pGrid.reset();
	}
	m_pCamera.reset();
	m_pCore.reset();
}
void Renderer::Render()
{
	UpdateFPS();

	m_pCore->Update();

	m_bShowGrid ? m_pCore->AddRenderData(m_pGrid) : 0;

	m_pCamera->Update();

	m_pCore->Render(m_pCamera);
	m_pCore->ClearRenderQueue();

	m_pCore->Present();
}
void Renderer::RenderPreview()
{
	m_pCore->Update();

	m_pCore->Render();
	m_pCore->ClearRenderQueue();

	m_pCore->Present();
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
	util_clear_objview_selection();
	util_update_obj_property_grid(ld3d::GameObjectPtr());

	Project::Instance()->SelectObject(ld3d::GameObjectPtr());
}
void Renderer::UpdateFPS()
{
	static int frame = 0;
	static int tick = GetTickCount();

	int dt = GetTickCount() - tick;

	if(dt > 500)
	{
		float fps = float(frame * 1000) / float(dt);
		util_update_status_bar_fps(fps);
		tick = GetTickCount();
		frame = 0;
	}
	frame++;
}
void Renderer::SetClearColor(const math::Color4& clr)
{
	m_pRS->SetClearColor(clr);
}
EditorCameraPtr	Renderer::GetCamera()
{
	return m_pCamera;
}