#pragma once

#include "core\RenderTarget.h"

namespace ld3d
{
	class D3D11RenderTarget : public RenderTarget
	{
	public:
		D3D11RenderTarget(ID3D11DeviceContext* pContext);
		virtual ~D3D11RenderTarget(void);

		bool											Create(int count, int w, int h, G_FORMAT formats[], int miplvls);
		int												GetRenderTargetCount();
		TexturePtr										AsTexture(int index);
		void											SetDepthStencilBuffer(DepthStencilBufferPtr pDepthBuffer);
		DepthStencilBufferPtr							GetDepthStencilBuffer();
		void											Release();

		virtual ID3D11DepthStencilView*					GetD3D11DepthStencilView();
		virtual ID3D11RenderTargetView**				GetD3D11RenderTargetViews();
		virtual ID3D11RenderTargetView*					GetD3D11RenderTargetView(int index);

		int												GetWidth(int index);
		int												GetHeight(int index);
	private:

	protected:
		ID3D11RenderTargetView**						m_pRTViews;
		ID3D11Device*									m_pDevice;
		ID3D11DeviceContext*							m_pContext;
		std::vector<TexturePtr>							m_pTexures;
		DepthStencilBufferPtr							m_pDepthBuffer;

		int												m_width;
		int												m_height;
	};
}
