#pragma once

#include "core\Sys_Graphics.h"


namespace engine
{
	class D3D11Graphics : public Sys_Graphics
	{
	public:
		D3D11Graphics(void);
		virtual ~D3D11Graphics(void);


		bool									Initialize(const GraphicsSetting& setting);
		void									Release();

		void									SetPrimitiveType(PRIMITIVE_TYPE pt);
		void									DrawPrimitive(int count, int startindex, int basevertex);
		
		void									ClearRenderTarget(RenderTargetPtr pTarget, const math::Color4& clr, float d, int s, CLEAR_RENDERTARGET_FLAG flag); 
		void									Present();


		void									SetIndexBuffer(GPUBufferPtr pBuffer, G_FORMAT type);
		void									SetVertexBuffer(GPUBufferPtr pBuffer, unsigned int offset, unsigned int stride);

		GPUBufferPtr							CreateBuffer(BUFFER_TYPE type, int bytes, void* pInitData, bool dynamic);

		MaterialPtr									CreateMaterialFromFile(const char* szFile);

		TexturePtr								CreateTextureFromFile(const char* szFile);
		void									SetRenderTarget(RenderTargetPtr pRenderTarget);
		void									SetRenderTarget(MultiRenderTargetPtr pRT);
		TexturePtr								CreateTexture(TEXTURE_TYPE type, G_FORMAT format, int w, int h);

		
		MultiRenderTargetPtr					CreateMultiRenderTarget(int count, int w, int h, G_FORMAT formats[], int miplvls = 1);
		RenderTargetPtr							CreateRenderTarget(int w, int h, G_FORMAT format, int miplvls = 0);
		DepthStencilBufferPtr					CreateDepthStencilBuffer(int w, int h, G_FORMAT format);

		void									ResizeFrameBuffer(int cx, int cy);
	private:
		GPUBufferPtr							CreateIndexBuffer(int bytes, void* pInitData, bool dynamic);
		GPUBufferPtr							CreateVertexBuffer(int bytes, void* pInitData, bool dynamic);
		GPUBufferPtr							CreateConstantBuffer(int bytes, void* pInitData);

		bool									CreateFrameBuffer();
		bool									CreateDepthStencilBuffer(const GraphicsSetting& setting);
		void									SetupViewport(int w, int h);
	private:

		ID3D11Device*							m_pDevice;
		ID3D11DeviceContext*					m_pContext;
		IDXGISwapChain*							m_pSwapChain;
		ID3D11RenderTargetView*					m_pFrameBuffer;
		ID3D11DepthStencilView*					m_pDepthStencilBuffer;

		GraphicsSetting							m_setting;
	};
}
