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

		void									SetPrimitiveType(PRIMITIVE_TYPE pt);
		void									DrawPrimitive(int count, int startindex, int basevertex);
		
		void									SetClearColor(const math::Color4& clr);
		void									SetClearDepth(float d);
		void									SetClearStencil(uint32 val);

		void									ClearFrameBuffer(CLEAR_RENDERTARGET_FLAG flag = 
																	CLEAR_RENDERTARGET_FLAG(
																	CLEAR_COLOR_BUFFER 
																	| CLEAR_DEPTHSTENCIL_BUFFER));
		void									Present();


		void									SetIndexBuffer(GPUBufferPtr pBuffer, G_FORMAT type);
		void									SetVertexBuffer(GPUBufferPtr pBuffer, unsigned int offset, unsigned int stride);

		GPUBufferPtr							CreateBuffer(BUFFER_TYPE type, int bytes, void* pInitData, bool dynamic);

		GFXPtr									CreateGFXFromFile(const char* szFile);

		TexturePtr								CreateTextureFromFile(const char* szFile);
		void									SetRenderTarget(RenderTargetPtr pRenderTarget, DepthStencilBufferPtr pDS);
		void									SetRenderTargets(const std::vector<RenderTargetPtr>& pTargets, DepthStencilBufferPtr pDS);


		

		RenderTargetPtr							CreateRenderTarget(TexturePtr pColorBuffer);
		DepthStencilBufferPtr					CreateDepthStencilBuffer();
	private:
		GPUBufferPtr							CreateIndexBuffer(int bytes, void* pInitData, bool dynamic);
		GPUBufferPtr							CreateVertexBuffer(int bytes, void* pInitData, bool dynamic);
		GPUBufferPtr							CreateConstantBuffer(int bytes, void* pInitData);
	private:

		ID3D11Device*							m_pDevice;
		ID3D11DeviceContext*					m_pContext;
		IDXGISwapChain*							m_pSwapChain;
		ID3D11RenderTargetView*					m_pFrameBuffer;
		ID3D11DepthStencilView*					m_pDepthStencilBuffer;

		math::Color4							m_clearColor;
		float									m_clearDepth;
		int										m_clearStencil;

	};
}
