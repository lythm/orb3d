#pragma once


class GridMesh : public engine::RenderData
{
public:
	GridMesh(void);
	virtual ~GridMesh(void);

	bool									Init(int size, int grid_size);
	void									Release();

	void									Render_Depth(engine::Sys_GraphicsPtr pSysGraphics);
	void									Render(engine::Sys_GraphicsPtr pSysGraphics);
	engine::GFXPtr							GetGFX();
	math::Matrix44							GetWorldMatrix();
private:
	int										m_size;
	int										m_gridSize;
	
	engine::GPUBufferPtr					m_pVB;
	engine::GPUBufferPtr					m_pIB;
	engine::GFXPtr							m_pGFX;

};

