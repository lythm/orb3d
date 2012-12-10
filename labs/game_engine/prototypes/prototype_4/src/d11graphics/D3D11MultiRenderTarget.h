#pragma once

#include "core\MultiRenderTarget.h"

namespace engine
{
	class D3D11MultiRenderTarget : public MultiRenderTarget
	{
	public:
		D3D11MultiRenderTarget(ID3D11DeviceContext* pContext);
		virtual ~D3D11MultiRenderTarget(void);

		bool											Create(int count, int w, int h, G_FORMAT formats[], int miplvls);
		RenderTargetPtr									GetRenderTarget(int index);
		int												GetRenderTargetCount();
		TexturePtr										AsTexture(int index);
		void											SetDepthStencilBuffer(DepthStencilBufferPtr pDepthBuffer);
		DepthStencilBufferPtr							GetDepthStencilBuffer();
		void											Release();

		ID3D11DepthStencilView*							GetD3D11DepthStencilView();
		ID3D11RenderTargetView**						GetD3D11RenderTargetViews();
	private:

		ID3D11RenderTargetView**						m_pRTViews;

		ID3D11DeviceContext*							m_pContext;
		std::vector<RenderTargetPtr>					m_RTs;
		DepthStencilBufferPtr							m_pDepthBuffer;
	};
}