#pragma once


class GridMesh : public ld3d::RenderData
{
public:
	GridMesh(void);
	virtual ~GridMesh(void);

	bool									Init(ld3d::CoreApiPtr pCore, int size, int grid_size);
	void									Release();

	void									Render_Depth(ld3d::Sys_GraphicsPtr pSysGraphics);
	void									Render(ld3d::Sys_GraphicsPtr pSysGraphics, ld3d::MaterialPtr pMaterial = ld3d::MaterialPtr());
	ld3d::MaterialPtr						GetMaterial();
	math::Matrix44							GetWorldMatrix();

	bool									IsDeferred();
private:
	int										m_size;
	int										m_gridSize;
	
	ld3d::GPUBufferPtr					m_pVB;
	ld3d::GPUBufferPtr					m_pIB;
	ld3d::MaterialPtr						m_pMaterial;

	ld3d::CoreApiPtr						m_pCore;

};

