#pragma once
class Renderer
{
public:
	Renderer(void);
	virtual ~Renderer(void);

	bool								Initialize();
	void								Release();
	void								Render();

private:
	GridMeshPtr							m_pGrid;
};

