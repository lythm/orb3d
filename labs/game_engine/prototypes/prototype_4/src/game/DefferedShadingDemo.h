#pragma once


class DefferedShadingDemo
{
public:
	DefferedShadingDemo(void);
	virtual ~DefferedShadingDemo(void);

	bool											Init(engine::CoreApiPtr pCore);
	void											Release();
	void											Update();


private:
	void											DrawQuad();
	void											DrawScene();
	void											Render();
	void											CreateScene();
	void											CreateQuad();
	void											OnWMEvent(engine::EventPtr pEvent);
private:
	engine::CoreApiPtr								m_pCore;

	engine::GPUBufferPtr							m_pVB;
	engine::GPUBufferPtr							m_pIB;

	engine::GFXPtr									m_pGFX;

	engine::TexturePtr								m_pTex;

	engine::MultiRenderTargetPtr					m_pRT;


	engine::GPUBufferPtr							m_pQuadIB;
	engine::GPUBufferPtr							m_pQuadVB;
	engine::GFXPtr									m_pQuadGFX;

};

