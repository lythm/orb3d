#pragma once
class Renderer
{
public:
	Renderer(void);
	virtual ~Renderer(void);

	bool								Initialize(int vpw, int vph);
	void								Release();
	void								Render();

	void								OnMouseMove(UINT nFlags, CPoint point);
private:
	void								UpdateSemantics();
private:
	GridMeshPtr							m_pGrid;

	EditorCameraPtr						m_pCamera;
};

