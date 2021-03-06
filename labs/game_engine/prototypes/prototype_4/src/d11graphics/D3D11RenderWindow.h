#pragma once

#include "D3D11RenderTarget.h"

namespace engine
{
	class D3D11RenderWindow : public D3D11RenderTarget
	{
	public:
		D3D11RenderWindow(ID3D11DeviceContext* pContext);
		virtual ~D3D11RenderWindow(void);


		int											GetRenderTargetCount();
		TexturePtr									AsTexture(int index);

		bool										Create(void* handle, int w, int h, G_FORMAT color_format, G_FORMAT ds_format, int backbufferCount, int multiSampleCount, int multiSampleQuality, bool windowed);
		void										Release();
		void										SetupViewport(int w, int h);

		void										Present();
		void										Resize(int cx, int cy);

		int											GetWidth();
		int											GetHeight();
	private:
		bool										CreateFrameBuffer();
	private:

		IDXGISwapChain*								m_pSwapChain;

		int											m_width;
		int											m_height;
		G_FORMAT									m_frameBufferFormat;
		G_FORMAT									m_dsFormat;
		int											m_backbufferCount;
		int											m_multiSampleCount;
		int											m_multiSampleQuality;
	};
}
