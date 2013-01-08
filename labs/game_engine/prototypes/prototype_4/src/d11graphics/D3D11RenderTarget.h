#pragma once


#include "core\RenderTarget.h"



namespace engine
{
	class D3D11RenderTarget : public RenderTarget
	{
	public:
		D3D11RenderTarget(ID3D11DeviceContext* pContext);
		virtual ~D3D11RenderTarget(void);

		bool										Create(int w, int h, G_FORMAT format, int miplvls);
		ID3D11RenderTargetView*						GetD3D11RenderTargetView();
		ID3D11DepthStencilView*						GetD3D11DepthStencilView();
		TexturePtr									AsTexture();

		void										Release();
		void										SetDepthStencilBuffer(DepthStencilBufferPtr pBuffer);
		DepthStencilBufferPtr						GetDepthStencilBuffer();

		void										Apply();
	private:

		ID3D11DeviceContext*						m_pContext;
		ID3D11Device*								m_pDevice;
		ID3D11RenderTargetView*						m_pRenderTargetView;

		TexturePtr									m_pTex;
		DepthStencilBufferPtr						m_pDepthBuffer;
	};
}
