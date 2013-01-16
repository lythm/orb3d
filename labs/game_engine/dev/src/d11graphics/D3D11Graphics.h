#pragma once

#include "core\Sys_Graphics.h"


namespace ld3d
{
	class D3D11RenderWindow;

	class D3D11Graphics : public Sys_Graphics
	{
	public:
		D3D11Graphics(void);
		virtual ~D3D11Graphics(void);

		const GraphicsSetting&					GetGraphicsSetting();

		bool									Initialize(const GraphicsSetting& setting);
		void									Release();

		void									SetPrimitiveType(PRIMITIVE_TYPE pt);
		void									DrawIndexed(int count, int startindex, int basevertex);
		void									Draw(int vertexCount, int baseVertex);

		void									ClearRenderTarget(RenderTargetPtr pTarget, int index, const math::Color4& clr);
		void									ClearDepthStencilBuffer(DepthStencilBufferPtr pTarget, CLEAR_DS_FLAG flag, float d, int s); 
		void									Present();

		void									VSSetConstantBuffer(GPUBufferPtr pBuffer);
		void									PSSetConstantBuffer(GPUBufferPtr pBuffer);
		void									SetIndexBuffer(GPUBufferPtr pBuffer, G_FORMAT type);
		void									SetVertexBuffer(GPUBufferPtr pBuffer, unsigned int offset, unsigned int stride);

		GPUBufferPtr							CreateBuffer(BUFFER_TYPE type, int bytes, void* pInitData, bool dynamic);

		MaterialPtr								CreateMaterialFromFile(const char* szFile);

		TexturePtr								CreateTextureFromFile(const char* szFile);
		void									SetRenderTarget(RenderTargetPtr pRT);
		TexturePtr								CreateTexture(TEXTURE_TYPE type, G_FORMAT format, int w, int h);

		
		RenderTargetPtr							CreateRenderTarget(int count, int w, int h, G_FORMAT formats[], int miplvls = 1);
		DepthStencilBufferPtr					CreateDepthStencilBuffer(int w, int h, G_FORMAT format);

		void									ResizeFrameBuffer(int cx, int cy);

		ShaderPtr								CreateShaderFromFile(const char* szFile);
		RenderStatePtr							CreateRenderState();

		RenderTargetPtr							CreateRenderWindow(void* handle, int w, int h, G_FORMAT color_format, G_FORMAT ds_format, int backbufferCount, int multiSampleCount, int multiSampleQuality, bool windowed);
		void									SetRenderWindow(RenderTargetPtr pWnd);
		RenderTargetPtr							GetDefaultRenderTarget();
		RenderTargetPtr							GetCurrentRenderTarget();
		int										GetFrameBufferWidth();
		int										GetFrameBufferHeight();

		void									SetViewPort(int x, int y, int w, int h);
	private:
		GPUBufferPtr							CreateIndexBuffer(int bytes, void* pInitData, bool dynamic);
		GPUBufferPtr							CreateVertexBuffer(int bytes, void* pInitData, bool dynamic);
		GPUBufferPtr							CreateConstantBuffer(int bytes, void* pInitData);

		bool									CreateDefaultRenderTarget(const GraphicsSetting& setting);
		bool									CreateFrameBuffer();
		bool									CreateDepthStencilBuffer(const GraphicsSetting& setting);
		
	private:

		ID3D11Device*							m_pDevice;
		ID3D11DeviceContext*					m_pContext;
		
		GraphicsSetting							m_setting;

		boost::shared_ptr<D3D11RenderWindow>	m_pDefaultRW;

		boost::shared_ptr<D3D11RenderWindow>	m_pCurrentRW;
		
		D3D11_VIEWPORT							m_viewPort;

	};
}
