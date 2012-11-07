#pragma once


class GridMesh
{
public:
	GridMesh(void);
	virtual ~GridMesh(void);

	bool									Init();
	void									Release();

	void									Render();

private:


	engine::GPUBufferPtr					m_pVB;
	engine::GPUBufferPtr					m_pIB;
	engine::GFXPtr							m_pGFX;

};

