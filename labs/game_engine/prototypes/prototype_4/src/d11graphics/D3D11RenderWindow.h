#pragma once

#include "core\RenderTarget.h"

namespace engine
{
	class D3D11RenderWindow: public RenderTarget
	{
	public:
		D3D11RenderWindow(ID3D11DeviceContext* pContext);
		virtual ~D3D11RenderWindow(void);

		bool										Create(void* handle, int w, int h, G_FORMAT color_format, G_FORMAT ds_format, int backbufferCount, int multiSampleCount, int multiSampleQuality, bool windowed);
		ID3D11RenderTargetView*						GetD3D11RenderTargetView();
		ID3D11DepthStencilView*						GetD3D11DepthStencilView();
		TexturePtr									AsTexture();

		void										Release();
		void										SetDepthStencilBuffer(DepthStencilBufferPtr pBuffer);
		DepthStencilBufferPtr						GetDepthStencilBuffer();
		void										SetupViewport(int w, int h);
	private:
		bool										CreateFrameBuffer();
	private:


		ID3D11DeviceContext*						m_pContext;
		ID3D11Device*								m_pDevice;
		ID3D11RenderTargetView*						m_pRenderTargetView;

		void*										m_wnd;									
		DepthStencilBufferPtr						m_pDepthBuffer;

		IDXGISwapChain*								m_pSwapChain;
	};
}
