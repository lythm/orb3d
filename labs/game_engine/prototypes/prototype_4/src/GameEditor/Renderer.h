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

	void								CreateObject_Empty();
	void								CreateObject_FromTemplate_Cube();
	void								CreateObject_FromTemplate_Sphere();
private:
	void								UpdateSemantics();

private:
	GridMeshPtr							m_pGrid;


	engine::MeshPtr						m_pGridMesh;

	EditorCameraPtr						m_pCamera;
};

