#pragma once
class Renderer
{
public:
	Renderer(void);
	virtual ~Renderer(void);

	void								Resize(int vpw, int vph);
	bool								Initialize(engine::CoreApiPtr pCore);
	void								Release();
	void								Render();

	void								OnMouseMove(UINT nFlags, CPoint point);
	void								OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void								OnMouseRButtonDown(UINT nFlags, CPoint point);
	void								OnMouseRButtonUp(UINT nFlags, CPoint point);
	void								OnMouseLButtonClick(UINT nFlags, CPoint point);

	void								ShowGrid(bool bShow);
	bool								ShowingGrid();
	void								UpdateFPS();

	void								SetClearColor(const math::Color4& clr);
private:
		
private:
	GridMeshPtr							m_pGrid;
	bool								m_bShowGrid;
	EditorCameraPtr						m_pCamera;
	engine::CoreApiPtr					m_pCore;
	engine::RenderSystemPtr				m_pRS;
};

