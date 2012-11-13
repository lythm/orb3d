#pragma once

#include "core\DepthStencilBuffer.h"

namespace engine
{
	class D3D11DepthStencilBuffer : public DepthStencilBuffer
	{
	public:
		D3D11DepthStencilBuffer(ID3D11DeviceContext* pContext);
		virtual ~D3D11DepthStencilBuffer(void);

		bool										Create(int w, int h, G_FORMAT format, bool asTexture = false);

		void										Release();

		ID3D11DepthStencilView*						GetD3D11DepthStencilView();

		TexturePtr									AsTexture(G_FORMAT format = G_FORMAT_UNKNOWN);
		void										Clear(float depth, int stencil);
	private:

		TexturePtr									CreateTexture(G_FORMAT format);
	private:

		bool										m_bAsTexture;
		ID3D11Texture2D*							m_pBuffer;
		ID3D11DeviceContext*						m_pContext;
		ID3D11Device*								m_pDevice;
		ID3D11DepthStencilView*						m_pDepthStencilView;

		TexturePtr									m_pTex;

	};
}
