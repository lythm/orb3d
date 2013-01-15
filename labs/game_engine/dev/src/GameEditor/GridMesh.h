#pragma once


class GridMesh : public engine::RenderData
{
public:
	GridMesh(void);
	virtual ~GridMesh(void);

	bool									Init(engine::CoreApiPtr pCore, int size, int grid_size);
	void									Release();

	void									Render_Depth(engine::Sys_GraphicsPtr pSysGraphics);
	void									Render(engine::Sys_GraphicsPtr pSysGraphics, engine::MaterialPtr pMaterial = engine::MaterialPtr());
	engine::MaterialPtr						GetMaterial();
	math::Matrix44							GetWorldMatrix();

	bool									IsDeferred();
private:
	int										m_size;
	int										m_gridSize;
	
	engine::GPUBufferPtr					m_pVB;
	engine::GPUBufferPtr					m_pIB;
	engine::MaterialPtr						m_pMaterial;

	engine::CoreApiPtr						m_pCore;

};

