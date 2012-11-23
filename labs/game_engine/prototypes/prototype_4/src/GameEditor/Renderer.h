#pragma once
class Renderer
{
public:
	Renderer(void);
	virtual ~Renderer(void);

	void								ResetViewPort(int vpw, int vph);
	bool								Initialize(int vpw, int vph);
	void								Release();
	void								Render();

	void								OnMouseMove(UINT nFlags, CPoint point);
	void								OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void								OnMouseRButtonDown(UINT nFlags, CPoint point);
	void								OnMouseRButtonUp(UINT nFlags, CPoint point);
private:
	void								UpdateSemantics();
private:
	GridMeshPtr							m_pGrid;

	EditorCameraPtr						m_pCamera;
};

