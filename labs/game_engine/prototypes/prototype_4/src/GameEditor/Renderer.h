#pragma once
class Renderer
{
public:
	Renderer(void);
	virtual ~Renderer(void);

	void								Resize(int vpw, int vph);
	bool								Initialize(int vpw, int vph);
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

private:
	void								UpdateSemantics();
	
private:
	GridMeshPtr							m_pGrid;


	engine::MeshPtr						m_pGridMesh;
	bool								m_bShowGrid;
	EditorCameraPtr						m_pCamera;
};

