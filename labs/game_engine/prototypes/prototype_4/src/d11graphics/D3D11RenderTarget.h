#pragma once

#include "core\RenderTarget.h"

namespace engine
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

	private:

	protected:
		ID3D11RenderTargetView**						m_pRTViews;
		ID3D11Device*									m_pDevice;
		ID3D11DeviceContext*							m_pContext;
		std::vector<TexturePtr>							m_pTexures;
		DepthStencilBufferPtr							m_pDepthBuffer;
	};
}
