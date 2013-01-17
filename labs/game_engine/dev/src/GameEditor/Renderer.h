#pragma once
class Renderer
{
public:
	Renderer(void);
	virtual ~Renderer(void);

	void								Resize(int vpw, int vph);
	bool								Initialize(ld3d::CoreApiPtr pCore);
	void								Release();
	void								Render();
	void								RenderPreview();

	void								OnMouseMove(UINT nFlags, CPoint point);
	void								OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void								OnMouseRButtonDown(UINT nFlags, CPoint point);
	void								OnMouseRButtonUp(UINT nFlags, CPoint point);
	void								OnMouseLButtonClick(UINT nFlags, CPoint point);

	void								ShowGrid(bool bShow);
	bool								ShowingGrid();
	void								UpdateFPS();

	void								SetClearColor(const math::Color4& clr);

	EditorCameraPtr						GetCamera();
private:
		
private:
	GridMeshPtr							m_pGrid;
	bool								m_bShowGrid;
	EditorCameraPtr						m_pCamera;
	ld3d::CoreApiPtr					m_pCore;
	ld3d::RenderSystemPtr				m_pRS;
};

