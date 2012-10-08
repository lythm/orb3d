#pragma once

#include "core\Sys_Graphics.h"


namespace engine
{
	class D3D11Graphics : public Sys_Graphics
	{
	public:
		D3D11Graphics(void);
		virtual ~D3D11Graphics(void);


		bool									Initialize(void* app_handle, uint32 width, uint32 height);
		void									Release();

		void									DrawPrimitive(int count, int startindex, int basevertex);
		void									Draw(RenderDataPtr pData);
		void									Render();


		void									SetViewTransform(const math::Matrix44& view);
		void									SetProjTransform(const math::Matrix44& proj);

		void									SetClearColor(const math::Color4& clr);
		void									SetClearDepth(float d);
		void									SetClearStencil(uint32 val);

		void									ClearRenderTarget();
				
		void									Present();


		void									SetIndexBuffer(GPUBufferPtr pBuffer);
		void									SetVertexBuffer(GPUBufferPtr pBuffer);

		GPUBufferPtr							CreateBuffer(BUFFER_TYPE type, int bytes, void* pInitData, bool dynamic);

		GFXPtr									CreateGFXFromFile(const char* szFile);

		//void									SetRenderTarget(Texture2DPtr pTarget)						= 0;
		//virtual ShaderPtr						CreateShader()												= 0;

		//virtual RenderDataPtr					CreateRenderData()											= 0;
		//virtual Texture2DPtr					CreateTexture2D()											= 0;

		//virtual TexturePtr					CreateRenderTarget()										= 0;



	private:

		GPUBufferPtr							CreateIndexBuffer(int bytes, void* pInitData, bool dynamic);
		GPUBufferPtr							CreateVertexBuffer(int bytes, void* pInitData, bool dynamic);
		GPUBufferPtr							CreateConstantBuffer(int bytes, void* pInitData);
	private:

	//	RenderQueue								m_queue;

		ID3D11Device*							m_pDevice;

		ID3D11DeviceContext*					m_pContext;

		IDXGISwapChain*							m_pSwapChain;

		ID3D11RenderTargetView*					m_pFrameBuffer;
		ID3D11DepthStencilView*					m_pDepthStencilBuffer;

		math::Color4							m_clearColor;
		float									m_clearDepth;
		int										m_clearStencil;


		 CGcontext								m_pCG;

		ID3D11Buffer*							m_pCB;
	};
}
