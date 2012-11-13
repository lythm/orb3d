#pragma once


class GridMesh : public engine::RenderData
{
public:
	GridMesh(void);
	virtual ~GridMesh(void);

	bool									Init();
	void									Release();

	void									Render(engine::Sys_GraphicsPtr pSysGraphics);

private:
	
	engine::GPUBufferPtr					m_pVB;
	engine::GPUBufferPtr					m_pIB;
	engine::GFXPtr							m_pGFX;

};

