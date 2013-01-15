#pragma once


class DefferedShadingDemo
{
public:
	DefferedShadingDemo(void);
	virtual ~DefferedShadingDemo(void);

	bool											Init(ld3d::CoreApiPtr pCore);
	void											Release();
	void											Update();


private:
	void											DrawQuad();
	void											DrawScene();
	void											Render();
	void											CreateScene();
	void											CreateQuad();
	void											OnWMEvent(ld3d::EventPtr pEvent);
private:
	ld3d::CoreApiPtr								m_pCore;

	ld3d::GPUBufferPtr							m_pVB;
	ld3d::GPUBufferPtr							m_pIB;

	ld3d::MaterialPtr								m_pMaterial;

	ld3d::TexturePtr								m_pTex;

	ld3d::RenderTargetPtr					m_pRT;


	ld3d::GPUBufferPtr							m_pQuadVB;
	ld3d::MaterialPtr								m_pQuadMaterial;

	ld3d::MeshPtr									m_pMesh;

};

